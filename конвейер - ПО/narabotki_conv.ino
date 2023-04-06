// подключение библиотеки MQTT 
#include "EspMQTTClient.h" 

// подключение библиотеки датчика расстояния
#include "NewPing.h"

// подключение библиотеки для WS2812b
#include "Adafruit_NeoPixel.h"

// пины шагового двигателя для конвейера
#define STEP_CONV     13
#define DIR_CONV      15

// пины шагового двигателя для сортирующей системы
#define STEP_SHOVEL   14
#define DIR_SHOVEL    12

// пины ультразвукового датчика
#define TRIG_PIN      0
#define ECHO_PIN      2

// максимальная дистанция датчика
#define MAX_DISTANCE  200

// пин подключения светодиодной ленты
#define PIXEL_PIN     4

// количество светодиодов на светодиодной ленте
#define PIXEL_COUNT   16  

// инициализация светодиодной ленты 
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// пин концевого датчика с стороны мотора сортирующей системы
#define ENDER         5

//
#define COLORS_NUM_FOR_START 2

// переменные для хранения данных о выбранном цвете
int red   = 0;
int green = 0;
int blue  = 0;
int white = 0;
int start = 0;

// подключение к серверу MQTT
EspMQTTClient client(
  "PREDPROF_RULIT",                                  // название сети Wi-Fi
  "https://www.youtube.com/watch?v=eBGIQ7ZuuiU",     // пароль от сети Wi-Fi
  "mqtt.by",                                         // IP/домен сервера
  "мой логин",                                       // логин от сервера
  "мой пароль",                                      // пароль от сервера
  "23124"                                            // имя устройства
);

//
int check_colors_col()
{
  int sum = red + green + blue + white;
  if (sum == COLORS_NUM_FOR_START){
    Serial.println("Успешно выбраны " + String(COLORS_NUM_FOR_START) + " цвета! Устройство готово к запускау!");
    client.publish("user/NESCR/message", "Успешно выбраны 2 цвета! Устройство готово к запускау!");
    return 0;
  }
  else if (sum > COLORS_NUM_FOR_START){
    Serial.println("Выбрано слишком много цветов. Для запуска нужно выбрать строго 2 цвета!!");
    client.publish("user/NESCR/message", "Успешно выбраны 2 цвета! Устройство готово к запускау!");
    return 1;
  }
  return 0;
}

void check_colors_start()
{
  int sum = red + green + blue + white;
  if (sum == COLORS_NUM_FOR_START){
    Serial.println("Успешно выбраны " + String(COLORS_NUM_FOR_START) + " цвета! Запуск системы!");
    client.publish("user/NESCR/message", "Успешно выбраны " + String(COLORS_NUM_FOR_START) + " цвета! Запуск системы!");
  }
  else if (sum > COLORS_NUM_FOR_START){
    Serial.println("Выбрано слишком много цветов. Для запуска нужно выбрать строго 2 цвета!!");
    client.publish("user/NESCR/message", "Успешно выбраны " + String(COLORS_NUM_FOR_START) + " цвета! Устройство готово к запускау!");
  }
}

// подписка на топики
void onConnectionEstablished() 
{ 
  client.subscribe("/user/NESCR/red",   [] (const String &payload) {
    red   = payload.toInt();
    if (check_colors_col() == 1)
    {
      client.publish("/user/NESCR/red", "0"); 
    }
  }); 
  client.subscribe("/user/NESCR/green", [] (const String &payload) {
    green = payload.toInt();
    if (check_colors_col() == 1)
    {
      client.publish("/user/NESCR/green", "0"); 
    }
  }); 
  client.subscribe("/user/NESCR/blue",  [] (const String &payload) {
    blue  = payload.toInt();
    if (check_colors_col() == 1)
    {
      client.publish("/user/NESCR/blue", "0"); 
    }
  });
  client.subscribe("/user/NESCR/white", [] (const String &payload) {
    white = payload.toInt();
    if (check_colors_col() == 1)
    {
      client.publish("/user/NESCR/white", "0"); 
    }
  });
  client.subscribe("/user/NESCR/start", [] (const String &payload) {
    start = payload.toInt();
    check_colors_start();
  }); 
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

// возврат системы сортировка в начальное положение
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


void ender_setup()
{
  pinMode(ENDER, INPUT_PULLUP);
}


void setup()
{
  strip_setup();
  ender_setup();
  return_shovel_to_centre();
  Serial.begin(9600);
}

void loop()
{

}
