#include <MD_DS3231.h>
#include <Wire.h>
#include <PololuLedStrip.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
/*
  Выход на дешифратор OUT1,2,3,4 (4,5,6,7) PD4,PD5,PD6,PD7
  Выход на управление анодами DIG1,2,3,4,5 (8,9,10,11,12) PB0,PB1,PB2,PB3,PB4
  Выход на пищалку BUZ 13 PB5
  Входы кнопок BTN1,2,3 16,15,14 PC2,PC1,PC0
  Вход сигнала низкого питания (не используется, либо как выход для сброса часов) LOW_POW 3 PD3
*/
#define PIN_INTERRUPT 2
#define LOW_POW 3 //Не используется, либо как выход для сброса часов
#define LED 17
#define BUZ 13
#define BTN1 16
#define BTN2 15
#define BTN3 14
#define TONEBTN 400
#define TONEBTNTIME 5
#define PRINTS(s)   Serial.print(F(s))
#define PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }
#define SEALEVELPRESSURE_HPA (1033) //1013.25
Adafruit_BME280 bme; // I2C
#define BME280_ADDRESS (0x76)

PololuLedStrip<LED> led;
#define LED_COUNT 4
rgb_color colors[LED_COUNT];

int d[5];
unsigned long Time_t = 0;
unsigned long Blink_t = 0;
unsigned long Btn_t = 0;
unsigned long Leds_t = 0;
volatile unsigned long Alarm_t = 0;
unsigned long AntiPoison_t = 0;
bool dot = false;
bool menu = false;
byte blink_dig = 0;
int num;
byte level = 0;
bool param[2] = {0, 0}; //0 будильник вкл/выкл
byte ledr = EEPROM.read(1);
byte ledg = EEPROM.read(2);
byte ledb = EEPROM.read(3);
byte LedPreset = EEPROM.read(4);
volatile bool alarm = false;
int alrmi = 0;
bool status;

void setup() {
  tone(BUZ, 262, 5);
  Serial.begin(38400);
  DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7); //Порты на выход, дешифратор
  DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4); //Порты на выход для анодов
  pinMode(BUZ, OUTPUT);
  pinMode(LOW_POW, INPUT);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(PIN_INTERRUPT, INPUT_PULLUP);
  attachInterrupt(0, cbAlarm1, FALLING);
  RTC.control(DS3231_INT_ENABLE, DS3231_ON);
  RTC.control(DS3231_A1_FLAG, DS3231_OFF);
  RTC.control(DS3231_12H, DS3231_OFF);
  RTC.setAlarm1Type(DS3231_ALM_DTHMS);
  param[0] = (RTC.status(DS3231_A1_INT_ENABLE) == DS3231_ON);
  status = bme.begin(BME280_ADDRESS);
  if (!status) {
    PRINTS("Could not find a valid BME280 sensor, check wiring!");
  }
}

void loop() {
  char  c;
  c = readNext();
  readCMD(c);
  leds();
  Alarm();
  if (!menu && level < 1) {
    showTime();
    showDot();
    if (millis() - AntiPoison_t > 10000) {
      AntiPoison_t = millis();
      AntiPoison();
    }
  }
  PrintDisplay(d, blink_dig);
  Button();
  RTC.control(DS3231_A1_FLAG, DS3231_OFF);  // clear the alarm flag
  RTC.control(DS3231_A2_FLAG, DS3231_OFF);  // clear the alarm flag
}
