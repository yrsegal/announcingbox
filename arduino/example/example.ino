// example code

#include <Adafruit_NeoPixel.h>

#define LED_PIN 3
#define NUM_LEDS 3

#define BUZZER 5

Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    leds.setPixelColor(i, led_color(i));
    tone(BUZZER, 100);
    leds.show();
    delay(3000);
    leds.setPixelColor(i, led_color(-1));
    noTone(BUZZER); 
    leds.show();
  }
  delay(10000);
}


uint32_t led_color(int code) {
  switch (code) {
    case 0:
      return leds.Color(255, 0, 0);
      break;
    case 1:
      return leds.Color(0, 255, 0);
      break;
    case 2:
      return leds.Color(0, 0, 255);
      break;
    default:
      return leds.Color(0, 0, 0);
      break;
  }
}