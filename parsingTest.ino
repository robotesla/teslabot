#define MAXSECTIONCOUNT 10
//#define DEBUG 1
//#define DEBUG_PARSE 1
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
    parseStringFromSerial();
    //#ifdef DEBUG
    printSections();
    //#endif
    clearSections();
  }
}
