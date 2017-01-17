#ifndef _LANTERN_AIR_QUALITY_VISUALIZER_H
#define _LANTERN_AIR_QUALITY_VISUALIZER_H

#include "leds.h"
#include "PMS3003A.h"

class Visualizer {
  public:
    void setup(const PMS3003A &sensor, const Leds &leds);
    void loop();
  private:
    void showRed();
    void showGreen();
    PMS3003A _sensor;
    Leds _leds;
    bool airIsGood = false;
};

#endif
