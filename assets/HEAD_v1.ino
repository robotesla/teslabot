#include <Servo.h>
#include <Stepper.h>
Stepper stepper(500, 2, 3, 4, 5);
#define MAXsectionsCOUNT 10
#define LEFT_STOPPER 11
#define RIGHT_STOPPER 12
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
int del;
int speedx;
int timex;
void setup() {
  pitch_servo.attach(9);
  pitch_servo.write(30);
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
  Serial.println("V aNG2");
  sp = 255 - constrain(sp, 0, 255);
  int servoangle = angle + del;
  for (int i = del; servoangle >= i; i++)
  {
    if (sections[1] == "STOP_ACTION")
    {

    }
    else
    {
      pitch_servo.write(i);
      Serial.println(i);
      delay(sp);
    }
  }
  Serial.println("succes");

}

void angservo2(int angle, int sp)
{
  del = 0;  //pitch_servo.read();
  sp = 255 - constrain(sp, 0, 255);
  int servoangle = angle + del;
  for (int i = del; servoangle <= i; i--)
  {
    if (Serial.available())
    {
      Serial.println("avaib");
      parseStringFromSerial();
      if (sections[0] == "HEAD")
      {
        if (sections[1] == "STOP_ACTION")
        {
          break;
        }
      }
    }
    else
    {
      pitch_servo.write(i);
      Serial.println(i);
      delay(sp);
    }
    Serial.println("wait");
  }
  Serial.println("succes");
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

byte stoppers()
{
  if (digitalRead(LEFT_STOPPER))
  {
    Serial.println("STOPPER LEFT");
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    return 1;
  }
  if (digitalRead(RIGHT_STOPPER))
  {
    Serial.println("STOPPER RIGHT");
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    return 1;
  }
  else
  {
    return 0;
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
        angservo(String(sections[2]).toInt(), String(sections[3]).toInt());
      }
      if (sections[1] == "PITCH_DOWN")
      {
        angservo2(String(sections[2]).toInt(), String(sections[3]).toInt());
      }
      if (sections[1] == "YAW_LEFT")
      {
        xdef = 1;
        imm = 1;
        storona = 1;

      }
      if (sections[1] == "YAW_RIGHT")
      {
        xdef = 1;
        imm = 1;
        storona = -1;
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
        speedx = String(sections[2]).toInt();
        speedx = map(speedx, 0 , 255 , 45 , 110);
        speedx = constrain(speedx, 45, 110);
        stepper.setSpeed(speedx);
      }

      clearsections();
      timex = millis();
      if (xdef == 1)
      {
        while (imm)
        {
          if (!stoppers())
          {
            Serial.println((millis() - timex) / 1000);
            stepper.step(10 * storona);//20 * storona
          }
          if (stoppers())
          {
            imm = 0;
            digitalWrite(2, LOW);
            digitalWrite(3, LOW);
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
          }
          if (Serial.available())
          {
            parseStringFromSerial();
            if (sections[0] == "HEAD")
            {
              if (sections[1] == "GET_ACTION")
              {
                if (storona == 0)
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
                digitalWrite(2, LOW);
                digitalWrite(3, LOW);
                digitalWrite(4, LOW);
                digitalWrite(5, LOW);
              }
            }
          }
        }
      }
    }
  }
}
