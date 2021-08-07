#ifndef RACE_CARS_H
#define RACE_CARS_H

#include "ieffect.h"
#include "leds.h"

#include <time.h>

struct car
{
    unsigned int pos;

    led::RGB color;

    bool dir;
};

#define NUM_CARS 1

car cars[NUM_CARS];

class race_cars : public ieffect
{
  public:
  race_cars( led::RGB* leds )
  : m_leds( leds )
  , m_index( 0 )
  {
     init();

     init_cars();
  }

  void init()
  {
      for( int i = 0; i < 1080; i++)
      {
          led::setLedColor( m_leds, i, led::color::black  );
      }
  }

  void init_cars()
  {
      srand( time( NULL ) );

      for( int i = 0; i < NUM_CARS; ++i )
      {
          cars[ i ].pos = rand() % 1080 + 1;
          cars[ i ].dir = ( ( rand() % 2 ) == 0 ? true : false );
          cars[ i ].color = led::color::green;
      }
  }

  void update()
  {
    init();

    for( int i = 0; i < NUM_CARS; i++)
    {

        if( ( (cars[i].pos+1) % 18 ) == 0 )
        {
            turn( i );
        }
        else
        {
          if( cars[i].dir )
          {
             cars[i].pos++;
          }
          else
          {
             cars[i].pos--;
          }
        }
      m_leds[ cars[i].pos ] = cars[i].color;

    }
  }

  void turn( int index )
  {
      cars[index].pos;
  }

  void reset()
  {
      m_index = 0;
  }

  private:

  led::RGB* m_leds;

  unsigned int m_index;
};
#endif // RACE_CARS_H
