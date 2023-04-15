// Erstellt von Johannes Tadeus Ranish

// Dieses Programm soll 3 Servos eines Windkraftanalagen models mit 4 potentiometern ansteuern.
// Dabei sollen 3 Potentiometer je einen Servo ansteuern und ein 'Master' Potentiometer der alle Servos gleichzeitig ansteuert.
// Außerdem dürfen gewisse Grenzwerte von den Servos nicht überschritten werden.
//___________________________________________________________________________________________________________________________________//

#include <Servo.h> // benötigte library um Servos anzusteuern

// benennung der Servos
Servo s1; 
Servo s2;
Servo s3;

// Pin zuweisung der Potentiometer (potm ist der 'Master' -> steuert alle Servos gleichzeitig)
int potm = A3; 
int pot1 = A2;
int pot2 = A1;
int pot3 = A0;

// positions variablen der Potentiometer erstellen
int posm;
int pos1;
int pos2;
int pos3;

void setup() {

// Pinzuweisung der Servos
  s1.attach(9);
  s2.attach(10);
  s3.attach(11);

// Servos auf start Position Stellen
  s1.write(0);
  s2.write(0);
  s3.write(0);

  delay(1000);    // zeitlassen, damit die servos die start Position erreichen können

Serial.begin(9600); // Tool zur Analyse der ein und ausgabe werte
}

void loop() {

// initiierung der temporären variablen für die Servos
  int valm = 0; 
  int val1 = 0;
  int val2 = 0;
  int val3 = 0;
  
  int akkT = 50; // zeitbereich in ms für den die kurzzeit mittelwerte errechnet werden

 //Grenze der Servoauslenkung festlegen (abhängig von dem Winkel des befestigten Arms am Servo) 
  int upRange = 110;
  int loRange = 70;

  int test = 0; // die variable 'test' kann eingesetzt werden um den serial grafen in der Arduino IDE zu verwenden


// Aulesen der Potis + Filterung --> die letzten 2 bit der gelesenen werte werden zusammengefasst --> 0-7 = 0; 8-15 = 8 etc.
// in der for schleife werden die werte des potis über den angegeben zeitraum addiert und dann durch die zeit geteilt um den Mittelwert zu erhalten.

posm = analogRead(potm) & 0b1111111111111100;
for (int i = 0; i < akkT; i++)
{
  valm = valm + posm;
}
posm = valm / akkT;

pos1 = analogRead(pot1) & 0b1111111111111100;
for (int i = 0; i < akkT; i++)
{
  val1 = val1 + pos1;
}
pos1 = val1 / akkT;

pos2 = analogRead(pot2) & 0b1111111111111100;
for (int i = 0; i < akkT; i++)
{
  val2 = val2 + pos2;
}
pos2 = val2 / akkT;

pos3 = analogRead(pot3) & 0b1111111111111100;
for (int i = 0; i < akkT; i++)
{
  val3 = val3 + pos3;
}
pos3 = val3 / akkT;


// saklierung der potentiometer Werte auf eine von den Servos lesbare grad Zahl
pos1 = map(pos1 + posm, 0, 2040, loRange, upRange);
pos2 = map(pos2 + posm, 0, 2040, loRange, upRange);
pos3 = map(pos3 + posm, 0, 2040, loRange, upRange);

// Position an Servos witergeben
s1.write(pos1);
s2.write(pos2);
s3.write(pos3);

Serial.println(test); // den zu testenden wert ausgeben, damit er in der Arduino IDE getracked werden kann.
}