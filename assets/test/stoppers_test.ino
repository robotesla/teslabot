void setup()
{
  Serial.begin(9600);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
}



byte stoppers()
{
  if (digitalRead(11))
  {
    Serial.println("STOPPER LEFT");
    return 1;
  }
  if (digitalRead(12))
  {
    Serial.println("STOPPER RIGHT");
    return 1;
  }
  else
  {
    return 0;
  }
}
void loop()
{
  if (stoppers())
  {
    Serial.println("OK");
  }
}
