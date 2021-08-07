#ifndef IEFFECT_H
#define IEFFECT_H

class ieffect
{
  public:
  virtual ~ieffect(){}

  virtual void update() = 0;

  virtual void reset() = 0;

};


#endif // IEFFECT_H
