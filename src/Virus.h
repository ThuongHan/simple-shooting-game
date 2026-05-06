#ifndef VIRUS_INCLUDED
#define VIRUS_INCLUDED

#include "MySDL.h"
#include "Coord.h"
#include "Unit.h"

/*! A Virus, be careful!
 */
class Virus : public Unit
{
public:
    /*! Creates a Virus
      @param pos start position
      @param speed start speed
     */
    Virus(Coord pos, Coord speed) : Unit(pos, speed) {}
    void hit() override { kill(); }
    virtual int scoreValue() const { return 1; }
    bool isVirus() const override { return true; }
    double getRadius() const override { return radius; }

    /*! Draws the Virus
      @param mySDL for the size of the window
     */
    void draw(MySDL& mySDL) const override
    {   filledCircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(0,255,0)); }
    
protected:
    static const int radius=10;
};

#endif
