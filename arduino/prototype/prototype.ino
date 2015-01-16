#include <Time.h>
#include <Adafruit_NeoPixel.h>
#include <DigiCDC.h>

#define TIME_MSG_LEN 11
#define TIME_HEADER 't'
#define RESET_HEADER '*'
#define TIMESTAMP_MSG_LEN 7
#define TIMESTAMP_HEADER 'T'

#define LED_PIN 3
#define NUM_LEDS 3

#define BUZZER 5

int timestamps[256];
int colorstamps[256];
int lpos;

Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  SerialUSB.begin();
  pinMode(BUZZER, OUTPUT);
  int timestamps[256] = {};
  int colorstamps[256] = {};
  int lpos = 0;
}

void loop() {
  if (SerialUSB.available() > 0) {
    SerialUSB.println("rec");
    packetRecieve();
  }
  int tstamp = hmsTimeStamp();
  for (int i=0; i < lpos; i++) {
    if (tstamp == timestamps[i]) {
      leds.setPixelColor(colorstamps[i]-1, led_color(colorstamps[i]));
      tone(BUZZER, 100);
      leds.show();
      delay(300000);
      leds.setPixelColor(colorstamps[i]-1, led_color(-1));
      noTone(BUZZER); 
      leds.show();
    }
  }
}

uint32_c led_color(int code) {
  switch (code) {
    case 1:
      return leds.Color(255, 0, 0);
      break;
    case 2:
      return leds.Color(0, 255, 0);
      break;
    case 3:
      return leds.Color(0, 0, 255);
      break;
    default:
      return leds.Color(0, 0, 0);
      break;
  }
}

int hmsTimeStamp() {
	int timestamp = 3600*hour()+60*minute()+second();
	return (timestamp);
}


void packetRecieve() {
  // if time sync available from SerialUSB port, update time and return true
  while(SerialUSB.available() < TIME_MSG_LEN ){
  	delay(5);
  }
  while(SerialUSB.available() >=  TIME_MSG_LEN ){  // time message consists of a header and ten ascii digits
    char c = SerialUSB.read() ;
    SerialUSB.print(c);
    if( c == TIME_HEADER || c == RESET_HEADER) {
      if( c == RESET_HEADER ) {
        int timestamps[256] = {};
        int colorstamps[256] = {};
        int lpos = 0;
      }       
      time_t pctime = 0;
      for(int i=0; i < TIME_MSG_LEN -1; i++){   
        c = SerialUSB.read();
        SerialUSB.print(c);       
        if( c >= '0' && c <= '9'){   
          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number    
        }
      }   
      setTime(pctime);   // Sync Arduino clock to the time received on the SerialUSB port
      SerialUSB.print("-");
    }
  }
  while(SerialUSB.available() < TIMESTAMP_MSG_LEN ){
    delay(5);
  }
  while(SerialUSB.available() >= TIMESTAMP_MSG_LEN ){
    char c = SerialUSB.read() ;
    SerialUSB.print(c);
    if( c == TIMESTAMP_HEADER ) {
      int timestamp = 0;
      for(int i=0; i < TIMESTAMP_MSG_LEN - 2; i++){
        c = SerialUSB.read();
        SerialUSB.print(c);
        if( c >= '0' && c <= '9'){
          timestamp = (10 * timestamp) + (c - '0');
        }
      }
      SerialUSB.println();
      SerialUSB.println(timestamp);
      c = SerialUSB.read();
      SerialUSB.println(c);
      SerialUSB.println(lpos);
      timestamps[lpos] = timestamp;
      colorstamps[lpos] = c - '0';
      lpos++;
      lpos %= 255;
    }
  }
  SerialUSB.print(SerialUSB.available());
}
