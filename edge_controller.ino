

int pinCount = 8;
int motorAxisX[9] = {7, 6, 2, 3, 10, 9, 11, 12, 777};
int timer = 1500;
long schrittAnzahl = 0;
int taktAnzahl = 500; // Anzahl von schritten pro umdrehung
int leadScrewPitch = 0.5; // mm/umdrehung
//int linearBewegung = stepp / pitch // takt/mmm (linear)
long motorStepCount[3] = {0};


/*====================================================================================*/
void setup() {
  /*=====*/
  attachInterrupt(4,interrupt5,CHANGE);
  /*=====*/
  
  // SerialUSB.begin(9600);
  for (int i = 4; i < pinCount; i++) {
    pinMode(motorAxisX[i], OUTPUT);
    digitalWrite(motorAxisX[i], LOW);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(motorAxisX[i], INPUT_PULLUP);
  }
}
/*====================================================================================*/
void loop() {
  movement(scannerMatrix(motorAxisX), motorAxisX);
  //  SerialUSB.print();
}
/*====================================================================================*/
//INTERRUPT FUNKTIONEN
void interrupt5(){
SerialUSB.println("Interrupt!");
endStop(motorAxisX);
}
/*====================================================================================*/
//FUNKTIONEN
int count(int motorArray[]) {
  // zahlt wie oft ein knopf gedruckt wird, speichert
}
void SerialOutput() {
  // Gibt die momentan schritt anzahl pro motor.
}
/*============================================================================================================================================================*/

int scannerMatrix(int motor[]) {
  //scans for active buttons
  for (int i = 0; i < 4; i++) {
    if (digitalRead(motor[i]) == HIGH) {
      return i;
    }
  }
  return 999;
}
void movement(int scanner, int motor[]) {
  //wahl nach button von scanner welche bewegung funktion
  if (scanner < 4) {
    switch (scanner) {
      case 999:
        do_nothing();
        break;
      case 0:
        umdrehungPos(motor);
        break;
      case 1:
        umdrehungNeg(motor);
        break;
      case 2:
        einSchrittPos(motor);
        break;
      case 3:
        einSchrittNeg(motor);
        break;
    }
  }
}
void umdrehungPos(int motor[]) {
  // motor dreht 1 umdrehung in Postive achse richtung
  digitalWrite(motor[4], LOW);
  digitalWrite(motor[5], LOW);
  digitalWrite(motor[6], LOW);
  digitalWrite(motor[7], HIGH);
  int x = 0;
  delay(timer);
/*  for (int i = 4; i < pinCount; i++) {
    digitalWrite(motor, LOW);
  }
  switch (mark) {
      case 777:
      x = motorStepCount[3] + 500;
      motorStepCount[3] = x;
      break;
      case 999:
      do_nothing();
      break;
  } */
}
void umdrehungNeg(int motor[]) {
  // motor dreht 1 umdrehung in Negative achse richtung
  digitalWrite(motor[4], HIGH);
  digitalWrite(motor[5], LOW);
  digitalWrite(motor[6], LOW);
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
  }
}
void do_nothing() {
  // mach nichts
}
