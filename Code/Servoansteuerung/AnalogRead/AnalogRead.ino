void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
int val = 0;
int akkT = 20;
  // put your main code here, to run repeatedly:
// Serial.println(analogRead(A2));
int stableValue = analogRead(A2) & 0b1111111111111100;
// int sensVal = analogRead(A2);

for (int i = 0; i < akkT; i++)
{
  val = val + stableValue;
}

stableValue = val / akkT;

int pos = map(stableValue, 0, 1020, 45, 135);
Serial.println(pos);

delay(10);
}
