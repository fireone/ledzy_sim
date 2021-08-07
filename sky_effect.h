#ifndef SKY_EFFECT_H
#define SKY_EFFECT_H

#include "ieffect.h"
#include "leds.h"

#include <time.h>

#define NUM_STARS 100

namespace
{
struct star
{
  int intensity;

  int pos;

  bool dir;
};
}

star stars[NUM_STARS];

class sky_effect : public ieffect
{
  public:
  sky_effect( led::RGB* leds )
  : m_leds( leds )
  {
    init();
  }

  void init()
  {
      srand( time( NULL ) );

      for( int i = 0; i < NUM_STARS; i++)
      {
        stars[i].intensity = rand() % 255 + 1;
        stars[i].pos = rand() % 1080 + 1;
        stars[i].dir = ( ( rand() % 2 ) == 0 ? true : false );
      }
  }

  void update()
  {
    for( int i = 0; i < 1080; i++)
    {
        m_leds[i].r = 0;
        m_leds[i].g = 0;
        m_leds[i].b = 0;
    }

    for( int i = 0; i < NUM_STARS; i++)
    {
      if( stars[i].dir )
      {
        if( stars[i].intensity == 255 )
        {
          stars[i].dir = false;

          stars[i].intensity--;
        }

        stars[i].intensity++;
      }
      else
      {
        if( stars[i].intensity == 0 )
        {
            createStar( i );
        }
        else
        {
            stars[i].intensity--;
        }
      }

      m_leds[ stars[i].pos ].r = stars[i].intensity;
      m_leds[ stars[i].pos ].g = stars[i].intensity;
      m_leds[ stars[i].pos ].b = stars[i].intensity;
    }


  }

  void createStar( unsigned int index )
  {
      stars[index].dir = true;
      stars[index].intensity = 0;
      stars[index].pos = rand() % 1080 + 1;
  }

  void reset()
  {
      init();
  }

  private:

  led::RGB* m_leds;
};
#endif // SKY_EFFECT_H
