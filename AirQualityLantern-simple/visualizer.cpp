#include "visualizer.h"
// #include <cstring>

void Visualizer::setup(const PMS3003A &sensor, const Leds &leds) {
  _sensor = sensor;
  _leds = leds;
}


void Visualizer::loop() {
  airIsGood = _sensor.pm2_5 < 30;

  if (airIsGood) {
    showGreen();
  } else {
    showRed();
  }
}


void Visualizer::showRed() {
  _leds.setColor(20, 0, 0);
}


void Visualizer::showGreen() {
  _leds.setColor(0, 20, 0);
}
