void showTime() {
  RTC.readTime();
  d[1] = RTC.h / 10 % 10;
  d[2] = RTC.h % 10;
  d[3] = RTC.m / 10 % 10;
  d[4] = RTC.m % 10;
}

void showDate() {
  RTC.readTime();
  d[1] = RTC.dd / 10 % 10;
  d[2] = RTC.dd % 10;
  d[3] = RTC.mm / 10 % 10;
  d[4] = RTC.mm % 10;
}

void showYear() {
  RTC.readTime();
  d[1] = RTC.yyyy / 1000 % 10;
  d[2] = RTC.yyyy / 100 % 10;
  d[3] = RTC.yyyy / 10 % 10;
  d[4] = RTC.yyyy % 10;
}

void showAlarm1() {
  RTC.readAlarm1();
  d[1] = RTC.h / 10 % 10;
  d[2] = RTC.h % 10;
  d[3] = RTC.m / 10 % 10;
  d[4] = RTC.m % 10;
}

void showAlarm2() {
  RTC.readAlarm2();
  d[1] = RTC.h / 10 % 10;
  d[2] = RTC.h % 10;
  d[3] = RTC.m / 10 % 10;
  d[4] = RTC.m % 10;
}

void Alarm(){
  if (alarm) {
    if (millis() - Alarm_t > 20000) {
      Alarm_t = millis();
      alarm = false;
    }
    if (alrmi == 40) {
      tone(BUZ, 2200, 40);
    }
    if (alrmi == 48) {
      tone(BUZ, 2200, 40);
    }
    if (alrmi == 56) {
      tone(BUZ, 2200, 40);
    }
    if (alrmi == 64) {
      tone(BUZ, 2200, 40);
      alrmi = 0;
    }
    alrmi++;
  }
}

void cbAlarm1(void) {
  alarm = true;
  Alarm_t = millis();
  PRINTS("A1");
}
