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
  "название сети",
  "пароль",
  "mqtt.by",  // MQTT Broker server ip
  "мой юзер)",   // Can be omitted if not needed
  "иой пароль)",   // Can be omitted if not needed
  "23124"      // Client name that uniquely identify your device
);

// подписка на топики
void onConnectionEstablished() 
{ 
  client.subscribe("mytopic/test", [] (const String &payload) { red   = payload.toInt(); }); 
  client.subscribe("mytopic/test", [] (const String &payload) { green = payload.toInt(); }); 
  client.subscribe("mytopic/test", [] (const String &payload) { blue  = payload.toInt(); }); 
  client.subscribe("mytopic/test", [] (const String &payload) { white = payload.toInt(); }); 
  client.subscribe("mytopic/test", [] (const String &payload) { start = payload.toInt(); }); 
} 

//
void return_shovel_to_centre()
{
  while(!digitalRead(FIRST_BUTTON))
  {
    digitalWrite(DIR_SHOVEL, LOW);
    digitalWrite(STEP_SHOVEL, HIGH);  
  }
  digitalWrite(DIR_SHOVEL, HIGH);
  digitalWrite(STEP_SHOVEL, HIGH);   
  delay(1000);  
}


void setup()
{
  Serial.begin(9600);
  return_shovel_to_centre();
}

void loop()
{

}
