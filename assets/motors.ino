#include <NewPing.h>


#define EchoPinLeftF 5 //  + +
#define EchoPinLeftB 2  // + +
#define EchoPinRightF A2 // + +
#define EchoPinRightB A0 // + +
#define TrigPinLeftF 6 // +  +
#define TrigPinLeftB 9 //+ +
#define TrigPinRightF A3 // + +
#define TrigPinRightB 4  // + +

#define EN_A 10 // +
#define EN_B 11 // +
#define IN_1 8 //+
#define IN_2 7 //+
#define IN_3 3 //+
#define IN_4 A1 //+  // все пины проверены

#define MAX_DISTANCE 500

#define DEBUG 1
#define BASIC 2

//int WORK_MODE = DEBUG;
int WORK_MODE = BASIC;

NewPing sonarLF(TrigPinLeftF, EchoPinLeftF, MAX_DISTANCE);   //дальномеры
NewPing sonarLB(TrigPinLeftB, EchoPinLeftB, MAX_DISTANCE);
NewPing sonarRF(TrigPinRightF, EchoPinRightF, MAX_DISTANCE);
NewPing sonarRB(TrigPinRightB, EchoPinRightB, MAX_DISTANCE);

String incomingString;
String command;
String Section1;
String Section2;
String Section3;
String Section4;


void setup()
{
  Serial.begin(9600);  // установка порта на скорость 9600 бит/сек
  // Объявляем переменную для хранения введенного символа
  // put your setup code here, to run once:
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);


}

void loop()
{

  while (Serial.available()) {

    char incomingChar = Serial.read();

    incomingString += incomingChar;



    if (incomingChar == '\n') {

      //String stringOne = incomingString;
      int probel = incomingString.indexOf(' ');
      int probel2 = incomingString.indexOf(' ');
      int probel3 = incomingString.indexOf(' ');
      int probel4 = incomingString.indexOf(' ');
      
      Section1 = "na";
      Section2 = "na";
      Section3 = "na";
      Section4 = "na";
      //String stringOne = "<HTML><HEAD><BODY>";
      //int firstClosingBracket = stringOne.indexOf('>');
      // Serial.println("The index of > in the string " + stringOne + " is " + firstClosingBracket);
      //Serial.print (probel);

      Section1 = incomingString.substring (0, probel);
     incomingString = incomingString.substring (probel + 1, incomingString.length());

      probel = incomingString.indexOf(' ', probel);
//Serial.println (probel);
      Section2 = incomingString.substring (probel + 1, probel - 1);

 incomingString = incomingString.substring (probel + 1, incomingString.length());
      probel = incomingString.indexOf(' ', probel);
    //  Serial.println (probel);
      Section3 = incomingString.substring (probel + 1, probel - 1);

 incomingString = incomingString.substring (probel + 1, incomingString.length());
      probel = incomingString.indexOf(' ', probel);
     // Serial.println (probel);
      Section4 = incomingString.substring (probel + 1, probel - 1);
      // incomingString = incomingString.substring (probel+1, incomingString.length());

   Serial.println (Section1);
      Serial.println (Section2);
    Serial.println (Section3);
     //Serial.println (Section4); 

    }
  }
}
