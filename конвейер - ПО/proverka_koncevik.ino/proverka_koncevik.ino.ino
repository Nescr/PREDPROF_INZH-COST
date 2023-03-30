#define ENDER_IN 3

void setup()
{
  Serial.begin(9600);
  pinMode(ENDER_IN, INPUT_PULLUP);
}

void loop()
{
  Serial.println(!digitalRead(ENDER_IN));
  delay(100);
}