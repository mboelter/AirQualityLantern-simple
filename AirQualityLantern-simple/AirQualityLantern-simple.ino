//Uncomment this to see additional debugging information
#define DEBUG_LANTERN   true

#include <SoftwareSerial.h>
#include "PMS3003A.h"
#include "leds.h"

PMS3003A sensor;
Leds leds;

// D5: Software Serial Rx
// D7: Software Serial Tx - dont connect
SoftwareSerial swSer(D5, D7, false, 256);

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  
  #ifdef DEBUG_LANTERN
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  #endif
  
  setup_PMS();
  leds.setup();
}

void setup_PMS() {
  swSer.begin(9600);
}

void loop_PMS() {
  if (swSer.available()) {
    swSer.readBytes(sensor.buf, sensor.len);

    if (sensor.buf[0] == 0x42 && sensor.buf[1] == 0x4d) {
      if (sensor.update()) {
        #ifdef DEBUG_LANTERN
          Serial.print("pm1: \t");
          Serial.print(sensor.pm1);
          Serial.print("\t pm2.5: \t");
          Serial.print(sensor.pm2_5);
          Serial.print("\t pm10: \t");
          Serial.println(sensor.pm10);
        #endif
      }
    } else {
      // discard one more byte
      swSer.readBytes(sensor.buf,1);
    }
  }
}

void loop() {
  loop_PMS();

  if (sensor.pm2_5 < 30) {
    // air is good
    Serial.println("air is good. :-)");
    leds.setColor(0, 30, 0);
  } else if (sensor.pm2_5 < 60) {
    // air is not so good
    Serial.println("air is so-la-la. :-|");
    leds.setColor(77, 40, 10);
  } else {
    Serial.println("air is bad. :(");
    // air is bad
    leds.setColor(30, 0, 0);
  }
 
  
}
