#include "leds.h"

namespace led {

void setLedColor( led::RGB* leds, unsigned int index, led::RGB color )
{
    leds[index] = color;
}

}
