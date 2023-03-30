#define STEP_CONV     7
#define DIR_CONV      6
#define EN_PIN 8

void conv_forward()
{
  digitalWrite(DIR_CONV , HIGH);
  digitalWrite(STEP_CONV, HIGH); 
  delayMicroseconds(200);
  
  digitalWrite(STEP_CONV, LOW); 
  delayMicroseconds(200);
}

void conv_backward()
{
digitalWrite(DIR_CONV , LOW);
  digitalWrite(STEP_CONV, HIGH); 
  delayMicroseconds(200);

  digitalWrite(STEP_CONV, LOW); 
  delayMicroseconds(200);
}

void setup()
{
  pinMode(DIR_CONV, OUTPUT);
  pinMode(STEP_CONV, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);
}

void loop()
{
  
  for (int i=0; i < 1000; i++)
  {
    conv_forward();
  }

  for (int i=0; i < 1000; i++)
  {
    conv_backward();
  }
}