#ifndef DIAGONAL_ON_2_H
#define DIAGONAL_ON_2_H

#include "ieffect.h"
#include "leds.h"

class diagonal_on_2 : public ieffect
{
  public:
  diagonal_on_2( led::RGB* leds )
  : m_leds( leds )
  , m_index( 0 )
  {
     init();
  }

  void init()
  {
      for( int i = 0; i < 1080; i++)
      {
          led::setLedColor( m_leds, i, led::color::black  );
      }
  }

  void update()
  {
    if( m_index >= 180 )
    {
        return;
    }

    fill_diagonal( m_index,   led::RGB( 125, 125, 125) );
    fill_diagonal( m_index+1, led::RGB( 105, 105, 105) );
    fill_diagonal( m_index+2, led::RGB( 85, 85, 85) );
    fill_diagonal( m_index+3, led::RGB( 65, 65, 65) );
    fill_diagonal( m_index+4, led::RGB( 45, 45, 45) );
    fill_diagonal( m_index+5, led::RGB( 25, 25, 25 ) );

    m_index++;
  }

  void fill_diagonal(unsigned int index, led::RGB color)
  {
      if( index < 90 )
      {
          led::setLedColor( m_leds, index, color );
          led::setLedColor( m_leds, 540+89-index, color );
      }
      if( ( index > 17) && ( index < (18 + 90) ) )
      {
          led::setLedColor( m_leds, 180+17-index, color );
          led::setLedColor( m_leds, 540+89-17+index, color );
      }
      if( ( index > 17+18) && ( index < (18+18 + 90) ) )
      {
          led::setLedColor( m_leds, 180-36+index, color );
          led::setLedColor( m_leds, 540+179-35+90+90-19-index, color );
      }
      if( ( index > 17+18+18) && ( index < (18+18+18 + 90) ) )
      {
          led::setLedColor( m_leds, 360+17+36-index, color );
          led::setLedColor( m_leds, 540+269-17-36+index, color );
      }
      if( ( index > 17+18+18+18) && ( index < (18+18+18+18 + 90) ) )
      {
          led::setLedColor( m_leds, 360-72+index, color );
          led::setLedColor( m_leds, 540+359+90+90+90-36+18-17-73-index, color );
      }
      if( ( index > 17+18+18+18+18) && ( index < (18+18+18+18+18 + 90) ) )
      {
          led::setLedColor( m_leds, 540+17+72-index, color );
          led::setLedColor( m_leds, 90+540+180+90+index, color );
      }
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

#endif // DIAGONAL_ON_2_H
