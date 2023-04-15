// Erstellt von Johannes Tadeus Ranish

// Dieses Programm soll 3 Servos eines Windkraftanalagen models mit 4 potentiometern ansteuern.
// Dabei sollen 3 Potentiometer je einen Servo ansteuern und ein 'Master' Potentiometer der alle Servos gleichzeitig ansteuert.
// Außerdem dürfen gewisse Grenzwerte von den Servos nicht überschritten werden.



#include <Servo.h> // benötigte library um servos anzusteuern

Servo s1; // benennung der Servos
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

// initiierung einer temporären variable für die Servos
  int valm = 0;
  int val1 = 0;
  int val2 = 0;
  int val3 = 0;
  
  int akkT = 50; // zeitbereich für den die kurzzeit mittelwerte festgelegt werden

 //grenzen der Servos
  int upRange = 110;
  int loRange = 70;

// damit die Summe aus Master-wert und Poti-wert gebildet werden kann muss 90° abgezogen werden
  int upM = upRange - 90; 
  int loM = loRange - 90;

  int test = 0; // die variable 'test' kann eingesetzt werden um den serial grafen in der Arduino IDE zu verwenden

posm = analogRead(potm) & 0b1111111111111100; // Aulesen dess Potis + Filterung --> die letzten 2 bit der gelesenen werte werden zusammengefasst --> 0-7 = 0; 8-15 = 8 etc.
for (int i = 0; i < akkT; i++)
{
  valm = valm + posm;
}
posm = valm / akkT;                           // mittelwertbildung über die angegebene Zeit
posm = map(posm, 0, 1020, loM, upM);          // skalierung der potentiometer werte auf Servo lesbare grad zahlen


pos1 = analogRead(pot1) & 0b1111111111111100;
for (int i = 0; i < akkT; i++)
{
  val1 = val1 + pos1;
}
pos1 = val1 / akkT;
pos1 = map(pos1, 0, 1020, loRange, upRange);

if (pos1 + posm > loRange && pos1 + posm < upRange) { // überprüft ob die summierte position des Masters und Potis die Grenze nicht überschreitet
  s1.write(pos1 + posm);
  test = pos1 + posm;
  delay(15);
}
else {
  s1.write(pos1); // falls die Summe die Grenze überschreitet, wird nur die position des Potis an den Servo weitergegeben
}


pos2 = analogRead(pot2) & 0b1111111111111100;
for (int i = 0; i < akkT; i++)
{
  val2 = val2 + pos2;
}
pos2 = val2 / akkT;
pos2 = map(pos2, 0, 1020, loRange, upRange);

if (pos2 + posm > loRange && pos2 + posm < upRange) {
  s2.write(pos2 + posm);
  delay(15);
}
else {
  s1.write(pos2);
}


pos3 = analogRead(pot3) & 0b1111111111111100;
for (int i = 0; i < akkT; i++)
{
  val3 = val3 + pos3;
}
pos3 = val3 / akkT;
pos3 = map(pos3, 0, 1020, loRange, upRange);

if (pos3 + posm > loRange && pos3 + posm < upRange) {
  s3.write(pos3 + posm);
  delay(15);
}
else {
  s1.write(pos3);
}

Serial.println(test); // den zu testenden wert ausgeben, damit er in der Arduino IDE getracked werden kann.
}
