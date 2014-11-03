/*
 * rgb.ino
 * This file is part of arduino-nano-rgb
 *
 * Copyright (C) 2014 - Mirco Bertelli
 *
 * arduino-nano-rgb is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * arduino-nano-rgb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with arduino-nano-rgb. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Programma per Arduino Nano ATmega328.
 * Controlla il colore di un led RGB tramite un trimmer e un bottone.
 *
 * Premendo a lungo il bottone (almeno LHOLDTIME mSec) si entra in 'edit-mode'
 * ed, a questo punto, per ogni colore si può regolare l'intensità tramite il
 * trimmer. Una volta che un colore è stato regolato, si passa al successivo
 * premendo il tasto per almeno SHOLDTIME mSec. La selezione dei colori è
 * circolare. Per uscire dalla 'edit-mode' è necessario premere a lungo il
 * bottone.
 * 
 * L'ingresso nella edit-mode è segnalato attraverso un lampeggiamento del
 * colore che è al momento regolabile. Ogni volta che si seleziona un altro
 * colore, questo lampeggia per alcune volte.
 *
 * L'uscita dalla 'edit-mode' è segnalata dal lampeggiamento simultaneo di
 * tutti i colori.
 *
 * @file rgb.ino
 * @author Mirco Bertelli
 * @date lun 27 ott 2014, 18.52.20, CET
 */
#include <LiquidCrystal.h>

#define S0 -1 /**< stato iniziale */
#define R 0   /**< stato in cui si può regolare il ROSSO */
#define G 1   /**< stato in cui si può regolare il VERDE */
#define B 2   /**< stato in cui si può regolare il BLU   */

#define RPIN 9   /**< pin del colore ROSSO */
#define GPIN 10  /**< pin del colore VERDE */
#define BPIN 11  /**< pin del colore BLU */
#define BTN 4    /**< pin del bottone */
#define AIN 0    /**< pin dell'ingresso analogico usato */
#define NCOLOR 3 /**< numero dei colori */

#define MILS 10        /**< millisecondi di attesa tra le letture del bottone */
#define LHOLDTIME 1000 /**< attesa per entrare in edit-mode */
#define SHOLDTIME 20   /**< attesa per selezionare il colore da modificare */

#define LCD_RS_PIN 2 /**< il digital pin dove è collegato il pin RS del display */
#define LCD_E_PIN  3 /**< il digital pin dove è collegato il pin E del display */
#define LCD_D4_PIN 5 /**< il digital pin dove è collegato il pin D4 del display */
#define LCD_D5_PIN 6 /**< il digital pin dove è collegato il pin D5 del display */
#define LCD_D6_PIN 7 /**< il digital pin dove è collegato il pin D6 del display */
#define LCD_D7_PIN 8 /**< il digital pin dove è collegato il pin D7 del display */

int stato;         /**< lo stato corrente del sistema */
int value[NCOLOR]; /**< valori di luminosità dei vari colori */
int pin[NCOLOR];   /**< vettore dei pin dei colori */
int holdTime;      /**< durata bottone premuto */
int lcdValueColumn[NCOLOR]; /**< gli indici delle colonne del display dove scrivere i valori r,g,b */

// creo un istanza del display specificando i suo collegamento ad Arduino
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

void setup()
{
	// inizializzo il display specificando il numero di colonne e righe
	lcd.begin(16, 2);

	// configuro i pin dei colori
	pinMode(RPIN, OUTPUT);
	pinMode(GPIN, OUTPUT);
	pinMode(BPIN, OUTPUT);

	// configuro pin del bottone
	pinMode(BTN, INPUT);
	
	// imposto lo stato iniziale
	stato = S0;

	// inizializzo i valori di luminosità
	for(int i=0; i<NCOLOR; i++){
	    value[i] = 0;
	}

	// mappo i pin dei colori sul vettore
	pin[R] = RPIN;
	pin[G] = GPIN;
	pin[B] = BPIN;

	// il tasto non è stato ancora mai premuto...
	holdTime = 0;

	// imposto la luminosità dei vari colori
	// al momento tutto a 0
	for(int i=0; i<NCOLOR; i++){
		analogWrite(pin[i], value[i]);
	}

	lcd.setCursor(0, 0);
	lcd.print(" R   G   B  Edit");
	lcd.setCursor(0, 1);
	lcd.print("0   0   0   ----");

	// le colonne del display dove scrivere i valore per r, g & b
	lcdValueColumn[R] = 0;
	lcdValueColumn[G] = 4;
	lcdValueColumn[B] = 8;
}

void loop()
{
	switch (stato) {
	    case S0:{
	    	manageColorState(S0, R);
	    }break;
	    case R:{
	    	manageColorState(R, G);
	    }break;
	    case G:{
	    	manageColorState(G, B);
	    }break;
	    case B:{
	    	manageColorState(B, R);
	    }break;
	}
}

/**
 * Causa lo spostamento del sistema dallo stato corrente a quello
 * specificato. Stampa il nuovo stato sul display.
 *
 * @param state stato di destinazione.
 */
void switchTo(int state)
{
	stato = state;

	// scrivo sul display il colore che si stà modificando
	lcd.setCursor(12,1);
	if (state == S0)
		lcd.print("----");
	else if (state == R)
		lcd.print("Red  ");
	else if (state == G)
		lcd.print("Green");
	else
		lcd.print("Blu  ");
}

/**
 * Legge il valore analogico dal pin di input e aggiorna la luminosità
 * del colore specificato. Mostra il valore anche sul display.
 * 
 * @param colorPin pin sul quale è collegato il colore
 */
void editColor(int colorPin)
{
	// elimino il vecchio valore stampato sul display
	lcd.setCursor(lcdValueColumn[colorPin], 1);
	lcd.print("   ");
	lcd.setCursor(lcdValueColumn[colorPin], 1);

	value[colorPin] = (analogRead(AIN) >> 2);
	// stampo il nuovo valore
	lcd.print(value[colorPin], DEC);
	analogWrite(pin[colorPin], value[colorPin]);
	delay(100);
}

/**
 * Fa lampeggiare un solo colore.
 * Spegne tutti i colori, fa lampeggiare il colore specificato, ripristina tutti
 * i colori.
 *
 * @param p numero del pin sul quale è collegato il colore da far lampeggiare.
 * @param nBlink numero di lampi.
 */
void blink(int p, int nBlink)
{
	for(int i=0; i<NCOLOR; i++){
	    digitalWrite(pin[i], LOW);
	}
	delay(100);
	for(int i=0; i<nBlink; i++){
	    digitalWrite(p, HIGH);
	    delay(100);
	    digitalWrite(p, LOW);
	    delay(400);
	}
	for(int i=0; i<NCOLOR; i++){
	    analogWrite(pin[i], value[i]);
	}
}

/**
 * Lampeggiamento simultaneo di tutti i colori
 *
 * @param nBlink numero di lampeggiamenti da eseguire
 */
void blinkAll(int nBlink)
{
	for(int i=0; i<NCOLOR; i++){
	    digitalWrite(pin[i], LOW);
	}
	delay(100);

	for(int j=0; j<nBlink; j++){
		for(int i=0; i<NCOLOR; i++){
		    digitalWrite(pin[i], HIGH);
		}
		delay(100);
		
		for(int i=0; i<NCOLOR; i++){
		    digitalWrite(pin[i], LOW);
		}
		delay(400);
	}

	for(int i=0; i<NCOLOR; i++){
	    analogWrite(pin[i], value[i]);
	}
}

/**
 * Gestisce le operazioni da svolgere a seconda dello stato in cui si trova il
 * sistema.
 *
 * @param currentColorState stato corrente del sistema
 * @param nextColorState stato successivo nel quale migrare
 */
void manageColorState(int currentColorState, int nextColorState)
{
	if(digitalRead(BTN) == LOW){
	    if(holdTime == 0){
	    	if (currentColorState != S0)
		        editColor(currentColorState);
	    }else{
	    	if(holdTime >= LHOLDTIME){
	    		if (currentColorState != S0)
		    	    switchTo(S0);
		    	else
		    		switchTo(nextColorState);
	    	}else if(holdTime >= SHOLDTIME){
	    		if (currentColorState != S0){
		    		blink(pin[nextColorState], 3);
		    		switchTo(nextColorState);
		    	}
	    	}
	    	holdTime = 0;
	    }
	}else{
		if(holdTime == LHOLDTIME){
			if (currentColorState != S0)
				blinkAll(3);
			else
				blink(pin[nextColorState], 3);
	    }
		holdTime += MILS;
		delay(MILS);
	}
}
