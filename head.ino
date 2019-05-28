#include <Servo.h>
#include <Stepper.h>
Stepper stepper(20, 8, 9, 10, 11);
#define MAXsectionsCOUNT 10
//#define DEBUG 1
//#define DEBUG_PARSE 1
String sections[MAXsectionsCOUNT];
Servo pitch_servo;
int storona;
int xdef;
int imm;
int imm1;
int xdef1;
int storona1;
void setup() {
  pitch_servo.attach(11);
  pitch_servo.write(90);
  Serial.begin(9600);
#ifdef DEBUG
  Serial.println("start");
#endif
}

void parseStringFromSerial() {
  int sectionsIndex = 0;
  String section;

  while (Serial.available() > 0) {
#ifdef DEBUG_PARSE
    Serial.println("in while");
#endif
    delay(5);
    char incomingChar = Serial.read();
#ifdef DEBUG_PARSE
    Serial.print("sections: ");
    Serial.println(sections);
    Serial.print("sectionsIndex: ");
    Serial.println(sectionsIndex);
    Serial.print("incomingChar: ");
    Serial.println(incomingChar);
#endif
    if (incomingChar == ' ' || incomingChar == '\n') {
      sections[sectionsIndex] = section;
      section = "";
      ++sectionsIndex;
    } else {
      section += incomingChar;
    }
#ifdef DEBUG_PARSE
    Serial.println("at the end of while");
    Serial.print("sections: ");
    Serial.println(sections);
    Serial.print("sectionsIndex: ");
    Serial.println(sectionsIndex);
    Serial.print("incomingChar: ");
    Serial.println(incomingChar);
#endif
  }
}
void angservo(int angle, int sp)
{
  int servoangle = pitch_servo.read();
  if (servoangle < angle)
  {
    for (int del = servoangle; del = servoangle; del++)
    {
      pitch_servo.write(del);
      delay(sp);
    }
  }


}
void clearsections() {
  for (int i = 0; i < MAXsectionsCOUNT; ++i)
    sections[i] = "";
}

void printsections() {
  for (int i = 0; i < MAXsectionsCOUNT; ++i) {
    Serial.print("sections[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.println(sections[i]);
  }
}

void loop() {



  if (Serial.available() > 0) {

    parseStringFromSerial();
    printsections();


    if (sections[0] == "HEAD")
    {
      if (sections[1] == "PITCH_UP")
      {
        storona = 1;
        xdef = 1;
        imm = 1;
      }
      if (sections[1] == "PITCH_DOWN")
      {
        storona = -1;
        xdef = 1;
        imm = 1;

      }
      if (sections[1] == "YAW_LEFT")
      {
        xdef = 1;
        imm = 1;

      }
      if (sections[1] == "YAW_RIGHT")
      {
        xdef = 1;
        imm = 1;
      }
      if (sections[1] == "GET_ACTION")
      {
        Serial.println("STOP_ACTION");
      }
      if (sections[1] == "STOP_ACTION")
      {
        Serial.println("OK");
      }
      if (sections[2] != "")
      {
        stepper.setSpeed(String(sections[2]).toInt());
      }
      clearsections();
      if (xdef == 1)
      {
        while (imm)
        {
          stepper.step(20 * storona);
          if (Serial.available())
          {
            parseStringFromSerial();
            if (sections[0] == "HEAD")
            {
              if (sections[1] == "GET_ACTION")
              {
                if (storona == 1)
                {
                  Serial.println("YAW_LEFT");
                }
                else
                {
                  Serial.println("YAW_RIGHT");
                }
              }
              if (sections[1] == "STOP_ACTION")
              {
                xdef = 0;
                imm = 0;
              }
            }
          }
        }
        while (imm1)
          stepper.step(20 * storona);
        if (Serial.available())
        {
          if (sections[0] == "HEAD")
          {
            if (sections[1] == "GET_ACTION")
            {
              if (storona == 1)
              {
                Serial.println("PITCH_UP");
              }
              else
              {
                Serial.println("PITCH_DOWN");
              }

              if (sections[1] == "STOP_ACTION")
              {
                xdef1 = 0;
                imm1 = 0;
              }
            }
          }
        }
      }
    }
  }
}
