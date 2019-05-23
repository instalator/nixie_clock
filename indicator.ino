void showDot() {
  if (millis() - Time_t >= 1000) {
    Time_t = millis();
    dot = !dot;
  }
}

void AntiPoison() {
  for (byte x = 1; x < 5; x++) {
    for (byte i = 0; i < 10; i++) {
      d[x] = i;
      PrintDisplay(d, 0);
    }
    if(x == 1){d[x] = RTC.h /10 % 10;}
    if(x == 2){d[x] = RTC.h % 10;}
    if(x == 3){d[x] = RTC.m /10 % 10;}
    if(x == 4){d[x] = RTC.m % 10;}
  }
}

void PrintDisplay(int d[], byte dig) {
  if (dot) {
    d[0] = 0;
    setNumber(d[0]);
    PORTB |= (1 << PB4); //DIG5, HIGH
    delay(2);
    d[0] = 1;
    setNumber(d[0]);
    delay(2);
    PORTB &= ~(1 << PB4); //DIG5, LOW
  } else {
    PORTB &= ~(1 << PB4); //DIG5, LOW
    delay(4);
  }

  if ((dig == 1 || dig == 8) && millis() - Blink_t >= 500 && millis() - Blink_t < 1000) {
    PORTB &= ~((1 << PB0) | (1 << PB1)); //DIG1,2 - LOW
  } else {
    setNumber(d[1]);
    PORTB |= (1 << PB0); //DIG1 - HIGH
    delay(2);
    PORTB &= ~(1 << PB0); //DIG1 - LOW

    setNumber(d[2]);
    PORTB |= (1 << PB1);  //DIG2 - HIGH
    delay(2);
    PORTB &= ~(1 << PB1); //DIG2 - LOW
  }

  if ((dig == 2 || dig == 8) && millis() - Blink_t >= 500 && millis() - Blink_t < 1000) {
    PORTB &= ~((1 << PB2) | (1 << PB3)); //DIG3,4 - LOW
  } else {
    setNumber(d[3]);
    PORTB |= (1 << PB2); //DIG3 - HIGH
    delay(2);
    PORTB &= ~(1 << PB2); //DIG3 - LOW

    setNumber(d[4]);
    PORTB |= (1 << PB3); //DIG4 - HIGH
    delay(2);
    PORTB &= ~(1 << PB3); //DIG4 - LOW
  }

  if (millis() - Blink_t > 1000) {
    Blink_t = millis();
  }
}


void setNumber(int num) {
  delay(1);
  switch (num) {
    case 0:
      PORTD &= ~((1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
      break;
    case 1:
      PORTD |= (1 << PD4);
      PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));
      break;
    case 2:
      PORTD |= (1 << PD5);
      PORTD &= ~((1 << PD4) | (1 << PD6) | (1 << PD7));
      break;
    case 3:
      PORTD |= (1 << PD4) | (1 << PD5);
      PORTD &= ~((1 << PD6) | (1 << PD7));
      break;
    case 4:
      PORTD |= (1 << PD6);
      PORTD &= ~((1 << PD4) | (1 << PD5) | (1 << PD7));
      break;
    case 5:
      PORTD |= (1 << PD4) | (1 << PD6);
      PORTD &= ~((1 << PD5) | (1 << PD7));
      break;
    case 6:
      PORTD |= (1 << PD5) | (1 << PD6);
      PORTD &= ~((1 << PD4) | (1 << PD7));
      break;
    case 7:
      PORTD |= (1 << PD4) | (1 << PD5) | (1 << PD6);
      PORTD &= ~(1 << PD7);
      break;
    case 8:
      PORTD |= (1 << PD7);
      PORTD &= ~((1 << PD4) | (1 << PD5) | (1 << PD6));
      break;
    case 9:
      PORTD |= (1 << PD4) | (1 << PD7);
      PORTD &= ~((1 << PD5) | (1 << PD6));
      break;
  }
}
