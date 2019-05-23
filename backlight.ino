void leds() {
  if (LedPreset == 0) {
    setRGB(0,0,0);
  }
  if (LedPreset == 1) {
    setRGB(ledr,ledg,ledb);
  }
  if (LedPreset == 2) {
    uint16_t time = millis() >> 2;
    for (uint16_t i = 0; i < LED_COUNT; i++) {
      byte x = (time >> 2) - (i << 3);
      colors[i] = hsvToRgb((uint32_t)x * 359 / 256, 255, 255);
    }
    led.write(colors, LED_COUNT);
  }
  if (LedPreset == 3) {
    setRGB(60,14,0);
  }
}

void setRGB(byte r, byte g, byte b) {
  rgb_color color;
  color.red = r;
  color.green = g;
  color.blue = b;
  for (uint16_t i = 0; i < LED_COUNT; i++) {
    colors[i] = color;
  }
  led.write(colors, LED_COUNT);
}

rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v) {
  if (millis() - Leds_t > 10) {
    Leds_t = millis();
    uint8_t f = (h % 60) * 255 / 60;
    uint8_t p = (255 - s) * (uint16_t)v / 255;
    uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t r = 0, g = 0, b = 0;
    switch ((h / 60) % 6) {
      case 0: r = v; g = t; b = p; break;
      case 1: r = q; g = v; b = p; break;
      case 2: r = p; g = v; b = t; break;
      case 3: r = p; g = q; b = v; break;
      case 4: r = t; g = p; b = v; break;
      case 5: r = v; g = p; b = q; break;
    }
    return rgb_color(r, g, b);
  }
  return;
}
