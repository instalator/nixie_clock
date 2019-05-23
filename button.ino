void setting() {
  if (level == 1) { //Установка часов
    if (blink_dig == 1) {
      rangehour();
      RTC.h = num;
      d[1] = RTC.h / 10 % 10;
      d[2] = RTC.h % 10;
      RTC.writeTime();
    }
    if (blink_dig == 2) { //Установка минут
      rangeminutes();
      RTC.m = num;
      d[3] = RTC.m / 10 % 10;
      d[4] = RTC.m % 10;
      RTC.writeTime();
    }
  }
  if (level == 2) { //Установка часов будильника
    RTC.s = 0;
    if (blink_dig == 1) {
      rangehour();
      RTC.h = num;
      d[1] = RTC.h / 10 % 10;
      d[2] = RTC.h % 10;
      RTC.writeAlarm1(DS3231_ALM_HMS);
    }
    if (blink_dig == 2) { //Установка минут будильника
      rangeminutes();
      RTC.m = num;
      d[3] = RTC.m / 10 % 10;
      d[4] = RTC.m % 10;
      RTC.writeAlarm1(DS3231_ALM_HMS);
    }
  }
  if (level == 3) { //Будильник
    if (blink_dig == 1) {//Установка день недели будильника
      rangedow();
      RTC.dd = num;
      d[1] = RTC.dd / 10 % 10;
      d[2] = RTC.dd % 10;
      if (RTC.dd > 0) {
        RTC.setAlarm1Type(DS3231_ALM_DDHMS);
        RTC.writeAlarm1(DS3231_ALM_DDHMS);
      } else {
        RTC.setAlarm1Type(DS3231_ALM_HMS);
        RTC.writeAlarm1(DS3231_ALM_HMS);
      }
    }
    if (blink_dig == 2) { // Вкл/выкл будильник
      rangebool();
      param[0] = num;
      d[3] = 0;
      d[4] = param[0];
      if (param[0] > 0) {
        RTC.control(DS3231_A1_INT_ENABLE, DS3231_ON);
      } else {
        RTC.control(DS3231_A1_INT_ENABLE, DS3231_OFF);
      }
    }
  }
  if (level == 4) { // Установка даты
    if (blink_dig == 1) { //День
      rangedate();
      RTC.dd = num;
      d[1] = RTC.dd / 10 % 10;
      d[2] = RTC.dd % 10;
      RTC.writeTime();
    }
    if (blink_dig == 2) { //Месяц
      rangemounth();
      RTC.mm = num;
      d[3] = RTC.mm / 10 % 10;
      d[4] = RTC.mm % 10;
      RTC.writeTime();
    }
  }
  if (level == 5) { //установка даты год
    byte y1 = RTC.yyyy / 1000 % 10;
    byte y2 = RTC.yyyy / 100 % 10;
    byte y3 = RTC.yyyy / 10 % 10;
    byte y4 = RTC.yyyy % 10;
    if (blink_dig == 1) {
      rangeera();
      RTC.yyyy = num * 100 + y3 + y4;
      d[1] = RTC.yyyy / 1000 % 10;
      d[2] = RTC.yyyy / 100 % 10;
      RTC.writeTime();
    }
    if (blink_dig == 2) {
      rangeyear();
      RTC.yyyy = y1 * 1000 + y2 + num;
      d[3] = RTC.yyyy / 10 % 10;
      d[4] = RTC.yyyy % 10;
      RTC.writeTime();
    }
  }
  if (level == 6) { //Управление подсветкой выбор пресета
    if (blink_dig == 8) {
      rangeyear();
      LedPreset = num;
      d[1] = 0;
      d[2] = LedPreset / 100 % 10;
      d[3] = LedPreset / 10 % 10;
      d[4] = LedPreset % 10;
      leds();
    }
  }
  if (level == 7) { //Управление подсветкой Красный
    if (blink_dig == 8) {
      rangergb();
      ledr = num;
      d[1] = 1;
      d[2] = ledr / 100 % 10;
      d[3] = ledr / 10 % 10;
      d[4] = ledr % 10;
      leds();
    }
  }
  if (level == 8) { //Управление подсветкой Зеленый
    if (blink_dig == 8) {
      rangergb();
      ledg = num;
      d[1] = 2;
      d[2] = ledg / 100 % 10;
      d[3] = ledg / 10 % 10;
      d[4] = ledg % 10;
      leds();
    }
  }
  if (level == 9) { //Управление подсветкой Синий
    if (blink_dig == 8) {
      rangergb();
      ledb = num;
      d[1] = 3;
      d[2] = ledb / 100 % 10;
      d[3] = ledb / 10 % 10;
      d[4] = ledb % 10;
      leds();
    }
  }
}

void setlevel() {
  switch (level) {
    case 1:
      showTime();
      break;
    case 2:
      RTC.setAlarm1Type(DS3231_ALM_HMS);
      showAlarm1();
      break;
    case 3:
      param[0] = (RTC.status(DS3231_A1_INT_ENABLE) == DS3231_ON);
      d[1] = RTC.dd / 10 % 10;
      d[2] = RTC.dd % 10;
      d[3] = 0;
      d[4] = param[0];
      break;
    case 4:
      showDate();
      break;
    case 5:
      showYear();
      break;
    case 6:
      d[1] = 0;
      d[2] = LedPreset / 100 % 10;
      d[3] = LedPreset / 10 % 10;
      d[4] = LedPreset % 10;
      //blink_dig = 8;
      break;
    case 7:
      d[1] = 1;
      d[2] = ledr / 100 % 10;
      d[3] = ledr / 10 % 10;
      d[4] = ledr % 10;
      //blink_dig = 8;
      break;
    case 8:
      d[1] = 2;
      d[2] = ledg / 100 % 10;
      d[3] = ledg / 10 % 10;
      d[4] = ledg % 10;
      //blink_dig = 8;
      break;
    case 9:
      d[1] = 3;
      d[2] = ledb / 100 % 10;
      d[3] = ledb / 10 % 10;
      d[4] = ledb % 10;
      //blink_dig = 8;
      break;
      //default:
  }
  if (level > 9) {
    quitmenu();
  }
}

void Button() {
  if ((menu || level > 0) && millis() - Btn_t > 10000) {
    quitmenu();
  }
  if (digitalRead(BTN2) == 0 && !menu && millis() - Btn_t > 200) {
    beepBTN();
    dot = false;
    Btn_t = millis();
    menu = true;
    blink_dig = 1;
    level = 1;
  }
  if (menu) {
    if (digitalRead(BTN2) == 0 && millis() - Btn_t > 500) {
      Btn_t = millis();
      beepBTN();
      blink_dig++;
      if (blink_dig > 2) {
        blink_dig = 1;
        level++;
        if (level > 5) {
          blink_dig = 8;
        }
      }
      setlevel();
    }
    if (digitalRead(BTN1) == 0 && millis() - Btn_t > 200) {
      Btn_t = millis();
      beepBTN();
      if (blink_dig == 1) {
        num = d[1] * 10 + d[2];
      }
      if (blink_dig == 2) {
        num = d[3] * 10 + d[4];
      }
      if (blink_dig == 8) {
        num = (d[2] * 100) + (d[3] * 10) + d[4];
      }
      num++;
      setting();
    }
    if (digitalRead(BTN3) == 0 && millis() - Btn_t > 200) {
      Btn_t = millis();
      beepBTN();
      if (blink_dig == 1 && num > 0) {
        num = d[1] * 10 + d[2];
      }
      if (blink_dig == 2 && num > 0) {
        num = d[3] * 10 + d[4];
      }
      if (blink_dig == 8 && num > 0) {
        num = (d[2] * 100) + (d[3] * 10) + d[4];
      }
      num--;
      setting();
    }
  } else {
    if (digitalRead(BTN1) == 0 && millis() - Btn_t > 200) {
      Btn_t = millis();
      beepBTN();
      level++;
      setlevel();
    }
    if (digitalRead(BTN3) == 0 && millis() - Btn_t > 200) {
      Btn_t = millis();
      beepBTN();
      level++;
      showsensor();
    }
  }
}

void showsensor() {
  int t = (int)(bme.readTemperature() + 0.51);
  int h = (int)(bme.readHumidity() + 0.51);
  int p = (int)((bme.readPressure() * 0.0075) + 0.51);
  switch (level) {
    case 1:
      d[1] = t / 10 % 10;
      d[2] = t % 10;
      d[3] = h / 10 % 10;
      d[4] = h % 10;
      break;
    case 2:      
      d[1] = p / 1000 % 10;
      d[2] = p / 100 % 10;
      d[3] = p / 10 % 10;
      d[4] = p % 10;
      break;
      //default:
  }
  if (level > 2) {
    quitmenu();
  }
}

void quitmenu() {
  if (menu) {
    EEPROM.write(1, ledr);
    EEPROM.write(2, ledg);
    EEPROM.write(3, ledb);
    EEPROM.write(4, LedPreset);
  }
  level = 0;
  menu = false;
  blink_dig = 0;
}

int rangergb() {
  if (num > 254) num = 0;
  if (num < 0) num = 254;
}

int rangeera() {
  if (num > 25) num = 19;
  if (num < 19) num = 25;
}

int rangeyear() {
  if (num > 99) num = 0;
  if (num < 0)  num = 99;
}

int rangedate() {
  if (num > 31) num = 0;
  if (num < 0) num = 31;
}

int rangemounth() {
  if (num > 12) num = 0;
  if (num < 0) num = 12;
}

int rangebool() {
  if (num > 1) num = 0;
  if (num < 0) num = 1;
}

int rangedow() {
  if (num > 7) num = 0;
  if (num < 0) num = 7;
}

int rangehour() {
  if (num > 23) num = 0;
  if (num < 0) num = 23;
}

int rangeminutes() {
  if (num > 59) num = 0;
  if (num < 0) num = 59;
}

void beepBTN() {
  tone(BUZ, TONEBTN, TONEBTNTIME);
}
