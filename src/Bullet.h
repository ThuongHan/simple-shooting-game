#ifndef BULLET_INCLUDED
#define BULLET_INCLUDED

#include "MySDL.h"
#include "Unit.h"
#include "Coord.h"

class Bullet : public Unit
{
    public:
        Bullet(Coord pos, Coord speed) : Unit(pos, speed) {}

        void step(MySDL& mySDL) override 
        { 
            pos += speed; 
            
            // Kill the bullet if it goes outside the screen
            Coord screen = mySDL.size();
            if (pos.x < 0 or pos.x > screen.x or pos.y < 0 or pos.y > screen.y)
                kill();
        }
        void draw(MySDL& mySDL) const override
        { filledCircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(255,0,0)); }

        double getRadius() const override { return radius; }

    private:
        static const int radius=5;
};




#endif // BULLET_INCLUDED