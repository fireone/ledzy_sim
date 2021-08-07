#ifndef RUNNER_H
#define RUNNER_H

#include "ieffect.h"
#include "leds.h"

class runner : public ieffect
{
  public:
  runner( led::RGB* leds )
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
    init();

    m_leds[m_index].r = 255;
    m_leds[m_index].g = 255;
    m_leds[m_index].b = 255;

    m_index++;

    if( m_index == 1080) m_index = 0;
  }

  void reset()
  {
      m_index = 0;
  }

  private:

  led::RGB* m_leds;

  unsigned int m_index;
};
#endif // RUNNER_H
