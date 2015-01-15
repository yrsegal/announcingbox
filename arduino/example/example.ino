// example code

#include <FastLED.h>

#define LED_PIN1 3
#define LED_PIN2 4
#define LED_PIN3 5
#define NUM_LEDS 1
#define NUM_STRP 3

#define BUZZER 6

void setup() {

}

void loop() {
	for (int i = 0; i < 3; i++) {
		for (int j=0; j < NUM_LEDS; j++) {
      leds[colorstamps[i]][j] = led_color(colorstamps[i]);
    }
    tone(BUZZER, 100);
    FastLED.show();
    delay(3000);
    for (int j=0; j < NUM_LEDS; j++) {
      leds[colorstamps[i]][j] = CRGB::Black;
    }
    noTone(BUZZER); 
    FastLED.show();
	}
	delay(10000);
}


CRGB led_color(int code) {
  switch (code) {
    case 0:
      return CRGB::Red;
      break;
    case 1:
      return CRGB::Green;
      break;
    case 2:
      return CRGB::Blue;
      break;
    default:
      return CRGB::Black;
      break;
  }
}