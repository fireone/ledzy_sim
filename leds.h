#ifndef LEDS_H
#define LEDS_H

namespace led {

struct RGB
{
    RGB( unsigned char _r, unsigned char _g, unsigned char _b )
        : r( _r )
        , g( _g )
        , b( _b )
    {}

    RGB( unsigned char _c )
        : r( _c )
        , g( _c )
        , b( _c )
    {}

    RGB()
        : r( 0 )
        , g( 0 )
        , b( 0 )
    {}

    unsigned char r;
    unsigned char g;
    unsigned char b;
};

namespace color {

static RGB black(0,0,0);
static RGB white(255,255,255);
static RGB red(255,0,0);
static RGB green(0,255,0);
static RGB blue(0,0,255);

}

void setLedColor( led::RGB* leds, unsigned int index, led::RGB color );

}

#endif //LEDS_H
