#ifndef SERVO_H
#define SERVO_H
#include <ESP32Servo.h>
class SERVO
{
  public:
  SERVO(){};
  ~SERVO(){};

  void serHandler()
  {
    if (newPos!=lastPos)
    {
      isSerRegulating = 1;
      if (newPos>lastPos && serDel.del(40) )
      {
        ++lastPos;
        servo1.write(lastPos);
      }
      else if (newPos<lastPos && serDel.del(40) )
      {
        --lastPos;
        servo1.write(lastPos);
      }
    }
    if (newPos==lastPos && isSerRegulating==1) { isSerRegulating=0; }
  }
  
  void serMove(int deg) { if (deg >= serLlimit && deg <= serUlimit) { newPos = deg; } else {return;} }
  //void serFirstSet(int POS) { lastPos=POS; newPos=POS; } 
  int getLowerLimit(void) { return this->serLlimit; }
  int getUpperLimit(void) { return this->serUlimit; }
  
  private: //136 deg balans
  int lastPos{136};
  int newPos{136};
  int serLlimit{0};  // LEZY
  int serUlimit{136}; // STOI
  int START_POS {136};
  Kronos serDel;
};
#endif
