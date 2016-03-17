// initilize array 8 pins pro motor Erste VIER PINS SIND INPUT.
int motorAxisX[8] = {0, 7, 6, 2, 3, 10, 9, 11, 12};
int motorAxisY[8] = {0, 7, 6, 2, 3, 10, 9, 11, 12};
int motorAxisC[8] = {0, 7, 6, 2, 3, 10, 9, 11, 12};
int pinCount = 8; // muss immer 2k aus Nat. zahlen.
int inputPins = 4; //halfte von pinCount
int timer = 1500 //MOTOR I/O dauer in ms
            /*====================================================================================*/
void setup() {
  attachInterrupt(4, interrupt5, CHANGE); //IDEALEWEISE fuer an strom eingesetzt.
  for (int i = 4; i < pinCount; i++) {
    //pins 4-7 als Out einstellen
    pinMode(motorAxisX[i], OUTPUT);
    pinMode(motorAxisY[i], OUTPUT);
    pinMode(motorAxisC[i], OUTPUT);
    digitalWrite(motorAxisX[i], LOW);
  }
  for (int i = 0; i < 4; i++) {
    //pins 0-3 als IN einstellen
    pinMode(motorAxisX[i], INPUT_PULLUP);
    pinMode(motorAxisY[i], INPUT_PULLUP);
    pinMode(motorAxisC[i], INPUT_PULLUP);
  }
}
/*====================================================================================*/
void loop() {
  //warte auf knopfe
  movement(scannerMatrix(motorAxisX));
  movement(scannerMatrix(motorAxisY));
  movement(scannerMatrix(motorAxisC));
  delay(500); // halb sekunde warten
}
//INTERRUPT FUNKTIONEN
void interrupt5() {
  SerialUSB.println("Interrupt!");
  endStop(motorAxisX);
}
/*====================================================================================*/
//FUNKTIONEN
int scannerMatrix(int motor[]) {
  //aktiv taste scannen
  for (int i = 0; i < 4; i++) {
    if (digitalRead(motor[i]) == HIGH) {
      return i;
    }
  }
  return 999; // SERIAL DEBUG
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

/* I/O "mode" muss eingestellt nach PIN von obenen pin array
zb HHHL, oder LLHH, usw
*/
void umdrehungPos(int motor[]) {
  // motor dreht 1 umdrehung in Postive achse richtung
  digitalWrite(motor[4], LOW);
  digitalWrite(motor[5], LOW);
  digitalWrite(motor[6], LOW);
  digitalWrite(motor[7], HIGH);
  delay(timer);
  for (int i = 4; i < pinCount; i++) {
    digitalWrite(motorAxisX[i], LOW);
  }
}
void umdrehungNeg(int motor[]) {
  // motor dreht 1 umdrehung in Negative achse richtung
  digitalWrite(motor[4], LOW);
  digitalWrite(motor[5], LOW);
  digitalWrite(motor[6], HIGH);
  digitalWrite(motor[7], LOW);
  delay(timer);
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
  delay(timer);
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
  delay(timer);
  for (int i = 4; i < pinCount; i++) {
    digitalWrite(motorAxisX[i], LOW);
  }
}
void endStop(int motor[]) {
  // motor dreht 1 SCHRITT in Negative achse richtung
  digitalWrite(motor[4], HIGH);
  digitalWrite(motor[5], HIGH);
  digitalWrite(motor[6], HIGH);
  digitalWrite(motor[7], HIGH);
  for (int i = 4; i < pinCount; i++) {
    digitalWrite(motorAxisX[i], LOW);
    digitalWrite(motorAxisY[i], LOW);
    digitalWrite(motorAxisC[i], LOW);
  }
}
void do_nothing() {
  // mach nichts
}
