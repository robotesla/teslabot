#include <NewPing.h>

#define EchoPinLeftF 5 //  + +
#define EchoPinLeftB 2  // + +
#define EchoPinRightF A2 // + +
#define EchoPinRightB A0 // + +
#define TrigPinLeftF 6 // +  +
#define TrigPinLeftB 9 //+ 
#define TrigPinRightF A3 // + +
#define TrigPinRightB 4  // + +
#define EN_A 10 // +
#define EN_B 11 // 
#define IN_1 8 //+
#define IN_2 7 //+
#define IN_3 3 //+
#define IN_4 A1 //+  
#define CALIBRATE_SPEED_L  0
#define CALIBRATE_SPEED_R  0

#define MAX_DISTANCE 500
NewPing sonarLF(TrigPinLeftF, EchoPinLeftF, MAX_DISTANCE);   //дальномеры
NewPing sonarLB(TrigPinLeftB, EchoPinLeftB, MAX_DISTANCE);
NewPing sonarRF(TrigPinRightF, EchoPinRightF, MAX_DISTANCE);
NewPing sonarRB(TrigPinRightB, EchoPinRightB, MAX_DISTANCE);

#define MAXSECTIONCOUNT 10
// #define DEBUG 0
// #define DEBUG_PARSE 1
String sections[MAXSECTIONCOUNT];

void setup() {
  Serial.begin(9600);
#ifdef DEBUG
  Serial.println("start");
#endif
}

void parseStringFromSerial() {
  int sectionIndex = 0;
  String section;

  while (Serial.available() > 0) {
#ifdef DEBUG_PARSE
    Serial.println("in while");
#endif
    delay(5);
    char incomingChar = Serial.read();
#ifdef DEBUG_PARSE
    Serial.print("section: ");
    Serial.println(section);
    Serial.print("sectionIndex: ");
    Serial.println(sectionIndex);
    Serial.print("incomingChar: ");
    Serial.println(incomingChar);
#endif
    if (incomingChar == ' ' || incomingChar == '\n') {
      sections[sectionIndex] = section;
      section = "";
      ++sectionIndex;
    } else {
      section += incomingChar;
    }
#ifdef DEBUG_PARSE
    Serial.println("at the end of while");
    Serial.print("section: ");
    Serial.println(section);
    Serial.print("sectionIndex: ");
    Serial.println(sectionIndex);
    Serial.print("incomingChar: ");
    Serial.println(incomingChar);
#endif
  }
}

void clearSections() {
  for (int i = 0; i < MAXSECTIONCOUNT; ++i)
    sections[i] = "";
}

void printSections() {
  for (int i = 0; i < MAXSECTIONCOUNT; ++i) {
    Serial.print("sections[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.println(sections[i]);
  }
}

void loop() {

  if (Serial.available() > 0) {
#ifdef DEBUG
    Serial.println("in if");
    Serial.print("Serial.available: ");
    Serial.println(Serial.available());
    Serial.print("Serial.peek(): ");
    Serial.println(Serial.peek());
#endif
    if (Serial.available() > 0)
    {
      parseStringFromSerial();
      if (sections[0] == "MOTORS")
      {

        // for ros usage
        if (section[1] != "MANUAL_LEFT" && section[1] != "MANUAL_RIGHT" && section[1] != "MANUAL_STOP")
        {
          analogWrite(EN_A, String(sections[2]).toInt() + CALIBRATE_SPEED_L);
          analogWrite(EN_B, String(sections[2]).toInt() + CALIBRATE_SPEED_R);
        }
        

        if (sections[1] == "MOVE_FORWARD")
        {
          digitalWrite(IN_1, LOW);
          digitalWrite(IN_2, HIGH);
          digitalWrite(IN_3, HIGH);
          digitalWrite(IN_4, LOW);
        }
        if (sections[1] == "TURN_RIGHT")
        {
          digitalWrite(IN_1, HIGH);
          digitalWrite(IN_2, LOW);
          digitalWrite(IN_3, LOW);
          digitalWrite(IN_4, LOW);
        }
        if (sections[1] == "TURN_LEFT")
        {
          digitalWrite(IN_1, LOW);
          digitalWrite(IN_2, LOW);
          digitalWrite(IN_3, LOW);
          digitalWrite(IN_4, HIGH);
        }
        if (sections[1] == "STOP_ACTION")
        {
          digitalWrite(IN_1, LOW);
          digitalWrite(IN_2, LOW);
          digitalWrite(IN_3, LOW);
          digitalWrite(IN_4, LOW);
        }
        // for ros usage
        if (section[1] == "MANUAL_LEFT")
        {
          digitalWrite(IN_3, LOW);
          digitalWrite(IN_4, HIGH);
          analogWrite(EN_A, String(sections[2]).toInt() + CALIBRATE_SPEED_L);
        }
        else if (section[1] == "MANUAL_RIGHT")
        {
          digitalWrite(IN_1, HIGH);
          digitalWrite(IN_2, LOW);
          analogWrite(EN_B, String(sections[2]).toInt() + CALIBRATE_SPEED_R);
        }
        else if (section[1] == "MANUAL_STOP")
        {
          if (section[2] == "LEFT")
          {
            digitalWrite(IN_3, LOW);
            digitalWrite(IN_4, LOW);
          }
          else if (section[2] == "RIGHT")
          {
            digitalWrite(IN_1, LOW);
            digitalWrite(IN_2, LOW);
          }
          else if (section[2] == "BOTH")
          {
            digitalWrite(IN_1, LOW);
            digitalWrite(IN_2, LOW);
            digitalWrite(IN_3, LOW);
            digitalWrite(IN_4, LOW);
          }
        }

      }


      if (sections[0] == "SENSORS");
      {
        if (sections[1] == "0")
        {
          unsigned int uS0 = sonarLF.ping_cm();
          if (uS0 == 0) {
            delay(50);
            uS0 = sonarLF.ping_cm();

            if (uS0 == 0) {
              delay(50);
              uS0 = sonarLF.ping_cm();

              if (uS0 == 0) {
                Serial.println(uS0);
              }
            }
          }
          else
          {

            Serial.println(uS0);
          }
        }
        if (sections[1] == "1")
        {
          unsigned int uS1 = sonarLB.ping_cm();
          if (uS1 == 1) {
            delay(50);
            uS1 = sonarLB.ping_cm();

            if (uS1 == 1) {
              delay(50);
              uS1 = sonarLB.ping_cm();

              if (uS1 == 1) {
                Serial.println(uS1);
              }
            }
          }
          else
          {

            Serial.println(uS1);
          }
        }
        if (sections[1] == "2")
        {
          unsigned int uS2 = sonarRF.ping_cm();
          if (uS2 == 0) {
            delay(50);
            uS2 = sonarRF.ping_cm();

            if (uS2 == 0) {
              delay(50);
              uS2 = sonarRF.ping_cm();

              if (uS2 == 0) {
                Serial.println(uS2);
              }
            }
          }
          else
          {

            Serial.println(uS2);
          }
        }
        if (sections[1] == "3")
        {
          unsigned int uS3 = sonarRB.ping_cm();
          if (uS3 == 0) {
            delay(50);
            uS3 = sonarRB.ping_cm();

            if (uS3 == 0) {
              delay(50);
              uS3 = sonarRB.ping_cm();

              if (uS3 == 0) {
                Serial.println(uS3);
              }
            }
          }
          else
          {

            Serial.println(uS3);
          }
        }
      }
      clearSections();
    }
  }
}
