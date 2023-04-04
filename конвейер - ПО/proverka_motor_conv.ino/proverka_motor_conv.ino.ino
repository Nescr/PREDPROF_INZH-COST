#define STEP_CONV     13
#define DIR_CONV      15


void conv_backward()
{
  digitalWrite(DIR_CONV , HIGH);
  digitalWrite(STEP_CONV, HIGH); 
  delayMicroseconds(500);
  
  digitalWrite(STEP_CONV, LOW); 
  delayMicroseconds(500);
}

void conv_forward()
{
digitalWrite(DIR_CONV , LOW);
  digitalWrite(STEP_CONV, HIGH); 
  delayMicroseconds(500);

  digitalWrite(STEP_CONV, LOW); 
  delayMicroseconds(500);
}

void setup()
{
  pinMode(DIR_CONV, OUTPUT);
  pinMode(STEP_CONV, OUTPUT);
}

void loop()
{
  for (int i=0; i < 1000; i++)
  {
    conv_forward();
  }
}
