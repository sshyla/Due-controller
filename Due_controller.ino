// initilize array 8 pins pro motor Erste VIER PINS SIND INPUT.
int motorAxisX[8] = {0, 7, 6, 2, 3, 10, 9, 11, 12};
int motorAxisY[8] = {0, 7, 6, 2, 3, 10, 9, 11, 12};
int motorAxisC[8] = {0, 7, 6, 2, 3, 10, 9, 11, 12};
int pinCount = 8; // muss immer 2k aus Nat. zahlen.
int inputPins = 4;
/*====================================================================================*/
void setup() {
 // SerialUSB.begin(9600);
  for (int i = 4; i < pinCount; i++) {
    pinMode(motorAxisX[i], OUTPUT);
    pinMode(motorAxisY[i], OUTPUT);
    pinMode(motorAxisC[i], OUTPUT);
  }
  for (int i = 4; i < pinCount; i++) {
    digitalWrite(motorAxisX[i], LOW);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(motorAxisX[i], INPUT_PULLUP);
    pinMode(motorAxisY[i], INPUT_PULLUP);
    pinMode(motorAxisC[i], INPUT_PULLUP);
  }
}
/*====================================================================================*/
void loop() {
  movement(scannerMatrix(motorAxisX));
  movement(scannerMatrix(motorAxisY));
  movement(scannerMatrix(motorAxisC));
 // SerialUSB.print(scannerMatrix(motorAxisX));
  delay(1000);
}
/*====================================================================================*/
//FUNKTIONEN
int scannerMatrix(int motor[]) {
  //scans for active buttons
  for (int i = 0; i < 4; i++) {
    if (digitalRead(motor[i]) == HIGH) {
      return i;
    }
  }
  return 999;
}
void movement(int scanner) {
  //wahl nach button von scanner welche bewegung funktion
  if (scanner < 4) {
    switch (scanner) {
      case 999:
        do_nothing();
        break;
      case 0:
        umdrehungPos(motorAxisX);
        break;
      case 1:
        umdrehungNeg(motorAxisX);
        break;
      case 2:
        einSchrittPos(motorAxisX);
        break;
      case 3:
        einSchrittNeg(motorAxisX);
        break;
    }
  }
}
void umdrehungPos(int motor[]) {
  // motor dreht 1 umdrehung in Postive achse richtung
  digitalWrite(motor[4], HIGH);
  digitalWrite(motor[5], HIGH);
  digitalWrite(motor[6], HIGH);
  digitalWrite(motor[7], HIGH);
  delay(2000);
  for (int i = 4; i < pinCount; i++) {
    digitalWrite(motorAxisX[i], LOW);
  }
}
void umdrehungNeg(int motor[]) {
  // motor dreht 1 umdrehung in Negative achse richtung
  digitalWrite(motor[4], HIGH);
  digitalWrite(motor[5], LOW);
  digitalWrite(motor[6], LOW);
  digitalWrite(motor[7], HIGH);
  delay(2000);
  for (int i = 4; i < pinCount; i++) {
    digitalWrite(motorAxisX[i], LOW);
  }
}
void einSchrittPos(int motor[]) {
  // motor dreht 1 SCHRITT in Postive achse richtung
  digitalWrite(motor[4], LOW);
  digitalWrite(motor[5], HIGH);
  digitalWrite(motor[6], LOW);
  digitalWrite(motor[7], LOW);
  delay(2000);
  for (int i = 4; i < pinCount; i++) {
    digitalWrite(motorAxisX[i], LOW);
  }
}
void einSchrittNeg(int motor[]) {
  // motor dreht 1 SCHRITT in Negative achse richtung
  digitalWrite(motor[4], HIGH);
  digitalWrite(motor[5], LOW);
  digitalWrite(motor[6], HIGH);
  digitalWrite(motor[7], HIGH);
  delay(2000);
  for (int i = 4; i < pinCount; i++) {
    digitalWrite(motorAxisX[i], LOW);
  }
}
void do_nothing() {
  // mach nichts
}
