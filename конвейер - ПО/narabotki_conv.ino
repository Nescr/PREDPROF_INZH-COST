// подключение библиотеки MQTT 
#include "EspMQTTClient.h" 

// подключение библиотеки датчика расстояния
#include "NewPing.h"

// подключение библиотеки для WS2812b
#include "Adafruit_NeoPixel.h"

// пины шагового двигателя для конвейера
#define STEP_CONV     D7 
#define DIR_CONV      D8

// пины шагового двигателя для сортирующей системы
#define STEP_SHOVEL   D5
#define DIR_SHOVEL    D6

// пины ультразвукового датчика
#define TRIG_PIN      D3
#define ECHO_PIN      D4

// максимальная дистанция датчика
#define MAX_DISTANCE  200

// пин подключения светодиодной ленты
#define PIXEL_PIN     D2 

// количество светодиодов на светодиодной ленте
#define PIXEL_COUNT   16  

// инициализация светодиодной ленты 
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// пин концевого датчика с стороны мотора сортирующей системы
#define FIRST_BUTTON  D0

// пин концевого датчика с противоположной стороны от мотора сортирующей системы
#define SECOND_BUTTON D1

// переменные для хранения данных о выбранном цвете
int red   = 0;
int green = 0;
int blue  = 0;
int white = 0;
int start = 0;

// подключение к серверу MQTT
EspMQTTClient client(
  "PREDPROF_RULIT",
  "MEAV_TOP",
  "mqtt.by",
  "мой логин",
  "мой пароль",
  "23124"
);

// подписка на топики
void onConnectionEstablished() 
{ 
  client.subscribe("/user/NESCR/red",   [] (const String &payload) { red   = payload.toInt(); }); 
  client.subscribe("/user/NESCR/green", [] (const String &payload) { green = payload.toInt(); }); 
  client.subscribe("/user/NESCR/blue",  [] (const String &payload) { blue  = payload.toInt(); }); 
  client.subscribe("/user/NESCR/white", [] (const String &payload) { white = payload.toInt(); }); 
  client.subscribe("/user/NESCR/start", [] (const String &payload) { start = payload.toInt(); }); 
} 

// первоначальная настройка светодиодной ленты
void strip_setup()
{
  strip.begin();                    
  strip.show();                    
  strip.setBrightness(255);  
}


// движение сортирующей системы влево
void shovel_left()
{
  digitalWrite(DIR_SHOVEL , LOW);
  digitalWrite(STEP_SHOVEL, HIGH); 
  delayMicroseconds(100);
  digitalWrite(DIR_SHOVEL , LOW);
  digitalWrite(STEP_SHOVEL, LOW); 
  delayMicroseconds(100);
}

// движение сортирующей системы вправо 
void shovel_right()
{
  digitalWrite(DIR_SHOVEL , HIGH);
  digitalWrite(STEP_SHOVEL, HIGH); 
  delayMicroseconds(100);
  digitalWrite(DIR_SHOVEL , HIGH);
  digitalWrite(STEP_SHOVEL, LOW); 
  delayMicroseconds(100);
}

// движение конвейера вперёд
void conv_forward()
{
  digitalWrite(DIR_CONV , LOW);
  digitalWrite(STEP_CONV, HIGH); 
  delayMicroseconds(100);
  digitalWrite(DIR_CONV , LOW);
  digitalWrite(STEP_CONV, LOW); 
  delayMicroseconds(100);
}

// движение конвейера назад
void conv_backward()
{
  digitalWrite(DIR_CONV , HIGH);
  digitalWrite(STEP_CONV, HIGH); 
  delayMicroseconds(100);
  digitalWrite(DIR_CONV , HIGH);
  digitalWrite(STEP_CONV, LOW); 
  delayMicroseconds(100);
}

// возврат системы сортировка в начальное положение
void return_shovel_to_centre()
{
  while(!digitalRead(FIRST_BUTTON))
  {
    shovel_right();  
  }
  for (int i = 0; i < 1000; i++)
  {
    shovel_left();
  }
}

void setup()
{
  Serial.begin(9600);
  strip_setup();
  return_shovel_to_centre();
}

void loop()
{

}
