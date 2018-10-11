String inputString = "";
bool stringComplete = false;

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
}

void loop() {
  if (Serial.read() != -1)
    delay(200);
    Serial.println("Test message");
}
