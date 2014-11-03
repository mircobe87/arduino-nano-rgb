v 20130925 2
C 40000 40000 0 0 0 title-B.sym
C 50700 42600 1 0 0 arduino_nano_v3.sym
{
T 51100 42800 5 10 0 1 0 0 1
device=Arduino NANO
T 51800 43500 5 10 0 1 0 0 1
footprint=ARD_NANO
}
C 49500 44300 1 0 0 resistor-1.sym
{
T 49800 44700 5 10 0 0 0 0 1
device=RESISTOR
T 49700 44600 5 10 1 1 0 0 1
refdes=Rr
T 49500 44300 5 10 0 0 0 0 1
value=330
}
C 49500 43900 1 0 0 resistor-1.sym
{
T 49800 44300 5 10 0 0 0 0 1
device=RESISTOR
T 49700 44200 5 10 1 1 0 0 1
refdes=Rg
T 49500 43900 5 10 0 0 0 0 1
value=330
}
C 49500 43500 1 0 0 resistor-1.sym
{
T 49800 43900 5 10 0 0 0 0 1
device=RESISTOR
T 49700 43800 5 10 1 1 0 0 1
refdes=Rb
T 49500 43500 5 10 0 0 0 0 1
value=330
}
C 48600 46300 1 0 0 resistor-1.sym
{
T 48900 46700 5 10 0 0 0 0 1
device=RESISTOR
T 48800 46600 5 10 1 1 0 0 1
refdes=R
T 48600 46300 5 10 0 0 0 0 1
value=10k
}
C 55000 43900 1 90 0 resistor-variable-1.sym
{
T 54100 44700 5 10 0 0 90 0 1
device=VARIABLE_RESISTOR
T 55500 44600 5 10 1 1 180 0 1
refdes=Trim
T 55000 43900 5 10 0 0 0 0 1
value=100k
}
C 48200 43400 1 270 0 led-2.sym
{
T 48000 43100 5 10 1 1 0 0 1
refdes=Dr
T 48800 43300 5 10 0 0 270 0 1
device=LED
}
C 48700 43400 1 270 0 led-2.sym
{
T 48500 43100 5 10 1 1 0 0 1
refdes=Dg
T 49300 43300 5 10 0 0 270 0 1
device=LED
}
C 49200 43400 1 270 0 led-2.sym
{
T 49000 43100 5 10 1 1 0 0 1
refdes=Db
T 49800 43300 5 10 0 0 270 0 1
device=LED
}
C 49900 48000 1 90 0 switch-pushbutton-no-1.sym
{
T 49600 48400 5 10 1 1 90 0 1
refdes=BTN
T 49300 48400 5 10 0 0 90 0 1
device=SWITCH_PUSHBUTTON_NO
}
C 48000 46500 1 270 0 gnd-1.sym
C 54800 43200 1 0 0 gnd-1.sym
C 54300 47900 1 0 0 gnd-1.sym
C 49400 47300 1 0 0 gnd-1.sym
C 48700 41800 1 0 0 gnd-1.sym
N 49300 43400 49300 43600 4
N 49300 43600 49500 43600 4
N 48800 43400 48800 44000 4
N 48800 44000 49500 44000 4
N 48300 43400 48300 44400 4
N 48300 44400 49500 44400 4
N 50800 44400 50400 44400 4
N 50800 44000 50400 44000 4
N 50800 43600 50400 43600 4
N 48800 42500 48800 42100 4
N 48300 42500 48300 42300 4
N 48300 42300 48800 42300 4
N 48800 42300 49300 42300 4
N 49300 42300 49300 42500 4
N 53800 44400 54400 44400 4
N 54900 43900 54900 43500 4
N 53800 47600 54900 47600 4
N 54900 44800 54900 49500 4
N 43600 49500 54900 49500 4
N 49500 46400 50800 46400 4
N 49900 48000 49900 46400 4
N 48300 46400 48600 46400 4
N 49500 47600 50800 47600 4
N 53800 48400 54400 48400 4
N 54400 48400 54400 48200 4
C 43800 43000 1 0 0 lcd-qc1602a.sym
C 42800 46900 1 270 0 resistor-variable-1.sym
{
T 43700 46100 5 10 0 0 270 0 1
device=VARIABLE_RESISTOR
T 43200 46300 5 10 1 1 270 0 1
refdes=TrimC
}
C 42100 42700 1 0 0 gnd-1.sym
C 46500 42700 1 0 0 gnd-1.sym
N 43900 46400 43400 46400 4
N 42200 43000 42200 47200 4
N 42200 43200 43900 43200 4
N 42900 46000 42900 43200 4
N 43900 47200 42200 47200 4
N 43900 47600 42900 47600 4
N 42900 47600 42900 46900 4
N 46300 43600 46600 43600 4
N 46600 43600 46600 43000 4
N 50800 44800 46300 44800 4
N 50800 45200 46300 45200 4
N 50800 45600 46300 45600 4
N 50800 46000 46300 46000 4
N 46300 44000 47400 44000 4
N 47400 44000 47400 46800 4
N 47400 46800 50800 46800 4
N 50800 47200 47100 47200 4
N 47100 47200 47100 43200 4
N 47100 43200 46300 43200 4
N 43900 43600 43600 43600 4
N 43600 43600 43600 47600 4
N 49900 49000 49900 49500 4
N 43600 49500 43600 47600 4
