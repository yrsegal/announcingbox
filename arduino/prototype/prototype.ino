#include <Time.h>
#include <FastLED.h>
#define NUM_LEDS 5
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

int times[1] = {608};
int colors[1] = {"a"};

CRGB colorsfromkey(colorkey) {
  switch (colorkey) {
    case "a":
      return (CRGB::Red);
      break;
  }
}

void colorStrip(color) {
  for (int i; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show()
}

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
  Serial.write(currentTimestamp());
}

int currentTimestamp() {
  int timestamp = Time.hour()*60;
  timestamp += Time.minute();
  return(timestamp);
}

int checkTimes() {
  truth = 0;
  for (int i; i < times.length; i++) {
    if (currentTimeStamp() == times[i]) {
      truth = i;
    }
  }
  return(truth);
}

void loop() {
  timecheck = checkTimes();
  if (timecheck > 0) {
    colorStrip(colorsfromkey(colors[timecheck]))
  }
}
