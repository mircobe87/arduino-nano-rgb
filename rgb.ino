/**
 * Programma per Arduino Nano ATmega328.
 * Controlla il colore di un led RGB tramite un trimmer e un bottone.
 *
 * Premendo a lungo il bottone (almeno LHOLDTIME mSec) si entra in 'edit-mode'
 * ed, a questo punto, per ogni colore si può regolare l'intensità tramite il
 * trimmer. Una volta che un colore è stato regolato, si passa al successivo
 * premendo il tasto per almeno SHOLDTIME mSec. La selezione dei colori è
 * circolare. Per uscire dalla 'edit-mode' è necessario premere a lundo il
 * bottone.
 * 
 * L'ingresso nella edit-mode è segnalato attraverso un lampeggiamento del
 * colore che è al momento regolabile. Ogni volta che si seleziona un altro
 * colore, questo lampeggia per alcune volte.
 *
 * L'uscita dalla 'edit-mode' è segnalata dal lampeggiamento simultaneto di
 * tutti i colori.
 *
 * @file rgb.ino
 * @author Mirco Bertelli
 * @date lun 27 ott 2014, 18.52.20, CET
 */

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

#define MILS 10        /**< millisecondi di attesa tra le leture del bottone */
#define LHOLDTIME 1000 /**< attesa per entrare in edit-mode */
#define SHOLDTIME 20   /**< attesa per selezionare il colore da modificare */

int stato;         /**< lo stato corrente del sistema */
int value[NCOLOR]; /**< valori di luminosità dei vari colori */
int pin[NCOLOR];   /**< vettore dei pin dei colori */
int holdTime;      /**< durata bottone premuto */

void setup()
{
	// cofiguro i pin dei colori
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
 * specificato.
 *
 * @param state stato di destinazione.
 */
void switchTo(int state)
{
	stato = state;
}

/**
 * Legge il valore analogico dal pin di input e aggiorna la luminosità
 * del colore specificato.
 * 
 * @param colorPin pin sul quale è collegato il colore
 */
void editColor(int colorPin)
{
	value[colorPin] = (analogRead(AIN) >> 2);
	analogWrite(pin[colorPin], value[colorPin]);
	delay(100);
}

/**
 * Fa lampeggiare un solo colore.
 * Spegne tutti i colori, fa lampeggiare il colore specificato, ripristina tutti
 * i colori.
 *
 * @param p numero del pin sul quale è collecato il colore da far lampeggiare.
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
 * Lampeggiamento simultaneto di tutti i colori
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
 * Gestisce le operazioni da svolgere a seconta dello stato in cui si trova il
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