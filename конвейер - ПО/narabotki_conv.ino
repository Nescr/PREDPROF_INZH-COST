#include "EspMQTTClient.h" 

// пины шагового двигателя для сортирующей системы
#define STEP_SHOVEL   14
#define DIR_SHOVEL    12
#define ENDER         5
#define STEP_CONV     13
#define DIR_CONV      15


// переменные для хранения данных о выбранном цвете
int red   = 0;
int green = 0;
int blue  = 0;
int white = 0;
int start = 0;

// подключение к серверу MQTT
EspMQTTClient client(
  "123456789",
  "123456789",
  "mqtt.by",                                         
  "NESCR",                                    
  "nescr",                                     
  "23124"                                            
);

void onConnectionEstablished() 
{ 
  client.subscribe("/user/NESCR/red",   [] (const String &payload) { red   = payload.toInt(); }); 
  client.subscribe("/user/NESCR/green", [] (const String &payload) { green = payload.toInt(); }); 
  client.subscribe("/user/NESCR/blue",  [] (const String &payload) { blue  = payload.toInt(); });
  client.subscribe("/user/NESCR/white", [] (const String &payload) { white = payload.toInt(); });
  client.subscribe("/user/NESCR/start", [] (const String &payload) { start = payload.toInt(); }); 
} 

// движение конвейера вперёд
void conv_forward()
{
  digitalWrite(DIR_CONV,  LOW);
  digitalWrite(STEP_CONV, HIGH); 
  delayMicroseconds(800);
  digitalWrite(STEP_CONV, LOW); 
  delayMicroseconds(800);
}

// движение конвейера назад
void conv_backward()
{
  digitalWrite(DIR_CONV , HIGH);
  digitalWrite(STEP_CONV, HIGH); 
  delayMicroseconds(800);
  digitalWrite(STEP_CONV, LOW); 
  delayMicroseconds(800);
}

// движение сортирующей системы влево
void shovel_left()
{
  digitalWrite(DIR_SHOVEL,  LOW);
  digitalWrite(STEP_SHOVEL, HIGH); 
  delayMicroseconds(800);
  digitalWrite(STEP_SHOVEL, LOW); 
  delayMicroseconds(800);
}

// движение сортирующей системы вправо 
void shovel_right()
{
  digitalWrite(DIR_SHOVEL , HIGH);
  digitalWrite(STEP_SHOVEL, HIGH); 
  delayMicroseconds(800);
  digitalWrite(STEP_SHOVEL, LOW); 
  delayMicroseconds(800);
}

void return_shovel_to_centre()
{
  while (digitalRead(ENDER))
  {
    shovel_right();
  }
  for (int i = 0; i < 560; i++)
  {
    shovel_left();
  }
}

void sort_left()
{
  for (int i = 0; i < 200; i++)
  {
    shovel_right();
  }
  delay(2000);
  for (int i = 0; i < 400; i++)
  {
    shovel_left();
  }
  delay(2000);
  for (int i = 0; i < 200; i++)
  {
    shovel_right();
  }
  delay(2000);
}

void sort_right()
{
  for (int i = 0; i < 200; i++)
  {
    shovel_left();
  }
  delay(2000);
  for (int i = 0; i < 400; i++)
  {
    shovel_right();
  }
  delay(2000);
  for (int i = 0; i < 200; i++)
  {
    shovel_left();
  }
  delay(2000);
}

void motor_setup()
{
  pinMode(DIR_SHOVEL,  OUTPUT);
  pinMode(STEP_SHOVEL, OUTPUT);
  pinMode(DIR_CONV,  OUTPUT);
  pinMode(STEP_CONV, OUTPUT);
}

void setup()
{
  pinMode(ENDER, INPUT_PULLUP);
  motor_setup();
}

void loop()
{
  int summ = red + green + blue + white;
  if (start == 1 and summ == 2)
  {
    return_shovel_to_centre();
    while (start == 1)
    {
      conv_forward();
      client.loop();
    }
  }
  else
  {
    client.loop();
  }
}
