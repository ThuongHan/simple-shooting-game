#ifndef UNIT_INCLUDED
#define UNIT_INCLUDED
#include "MySDL.h"

class Unit
{
    public:
        Unit(Coord p, Coord s) : pos(p), speed(s) {}
        virtual void step(MySDL& mySDL)
        {
            pos+=speed;
            if (pos.x<0 || pos.x>mySDL.size().x)
            { speed.x=-speed.x; }
            if (pos.y<0 || pos.y>mySDL.size().y)
            { speed.y=-speed.y; }
        }
        virtual void draw(MySDL& mySDL) const = 0;

        virtual void keyboard(const Uint8*) {}
        /* 
           Since unit is a common base class for Player and Virus,
           keyboard() is defined as a virtual function that does nothing
           by default. Is is only overridden for Player, while Virus uses
           the default empty implementation.
        */

        virtual double getRadius() const { return 0; }
        Coord getPos() const { return pos; }
        virtual ~Unit() {}
        
        virtual void kill() { dead = true; }
        virtual bool isDead() const { return dead; }
        virtual void hit() {}
        virtual bool isVirus() const { return false; }
    protected:
        Coord pos, speed;
        bool dead = false; // Keep track of which units should be deleted (bullets, dead viruses)
};

#endif // UNIT_INCLUDED
