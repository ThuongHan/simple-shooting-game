#ifndef BIGVIRUS_INCLUDED
#define BIGVIRUS_INCLUDED

#include "Virus.h"
#include "MySDL.h"

class BigVirus : public Virus
{
    public:
        BigVirus(Coord pos, Coord speed) : Virus(pos, speed*0.5), hp(5) {}
        void hit() override
        {
            hp--;
            if (hp<=0) { kill(); }
        }
        int scoreValue() const override { return 2; }
        double getRadius() const override { return radius; }


        void draw(MySDL& mySDL) const override
        {   filledCircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(255,10,0)); }

    
    private:
        int hp=5; // hitpoints
        static const int radius = 18;
};



#endif // BIGVIRUS_INCLUDED