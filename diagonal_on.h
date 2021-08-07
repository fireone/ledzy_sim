#ifndef DIAGONAL_ON_H
#define DIAGONAL_ON_H

#include "ieffect.h"
#include "leds.h"

class diagonal_on : public ieffect
{
  public:
  diagonal_on( led::RGB* leds )
  : m_leds( leds )
  , m_index( 0 )
  {
     init();
  }

  void init()
  {
      for( int i = 0; i < 1080; i++)
      {
          m_leds[i].r = 0;
          m_leds[i].g = 0;
          m_leds[i].b = 0;
      }
  }

  void update()
  {
    if( m_index >= 180 )
    {
        return;
    }

    if( m_index < 90 )
    {
        m_leds[m_index].r = 255;
        m_leds[m_index].g = 255;
        m_leds[m_index].b = 255;

        m_leds[540+89-m_index].r = 255;
        m_leds[540+89-m_index].g = 255;
        m_leds[540+89-m_index].b = 255;
    }
    if( ( m_index > 17) && ( m_index < (18 + 90) ) )
    {
        m_leds[180+17-m_index].r = 255;
        m_leds[180+17-m_index].g = 255;
        m_leds[180+17-m_index].b = 255;

        m_leds[540+89-17+m_index].r = 255;
        m_leds[540+89-17+m_index].g = 255;
        m_leds[540+89-17+m_index].b = 255;
    }
    if( ( m_index > 17+18) && ( m_index < (18+18 + 90) ) )
    {
        m_leds[180-36+m_index].r = 255;
        m_leds[180-36+m_index].g = 255;
        m_leds[180-36+m_index].b = 255;

        m_leds[540+179-35+90+90-19-m_index].r = 255;
        m_leds[540+179-35+90+90-19-m_index].g = 255;
        m_leds[540+179-35+90+90-19-m_index].b = 255;
    }
    if( ( m_index > 17+18+18) && ( m_index < (18+18+18 + 90) ) )
    {
        m_leds[360+17+36-m_index].r = 255;
        m_leds[360+17+36-m_index].g = 255;
        m_leds[360+17+36-m_index].b = 255;

        m_leds[540+269-17-36+m_index].r = 255;
        m_leds[540+269-17-36+m_index].g = 255;
        m_leds[540+269-17-36+m_index].b = 255;
    }
    if( ( m_index > 17+18+18+18) && ( m_index < (18+18+18+18 + 90) ) )
    {
        m_leds[360-72+m_index].r = 255;
        m_leds[360-72+m_index].g = 255;
        m_leds[360-72+m_index].b = 255;

        m_leds[540+359+90+90+90-36+18-17-73-m_index].r = 255;
        m_leds[540+359+90+90+90-36+18-17-73-m_index].g = 255;
        m_leds[540+359+90+90+90-36+18-17-73-m_index].b = 255;
    }
    if( ( m_index > 17+18+18+18+18) && ( m_index < (18+18+18+18+18 + 90) ) )
    {
        m_leds[540+17+72-m_index].r = 255;
        m_leds[540+17+72-m_index].g = 255;
        m_leds[540+17+72-m_index].b = 255;

        m_leds[90+540+180+90+m_index].r = 255;
        m_leds[90+540+180+90+m_index].g = 255;
        m_leds[90+540+180+90+m_index].b = 255;
    }

    m_index++;
  }

  void reset()
  {
      init();

      m_index = 0;
  }

  private:

  led::RGB* m_leds;

  unsigned int m_index;
};

#endif // DIAGONAL_ON_H
