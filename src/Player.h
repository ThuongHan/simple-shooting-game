#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "MySDL.h"
#include "Coord.h"
#include "Unit.h"
#include "Bullet.h"

/*! The object representing the player in VirusGame
 */
class Player : public Unit
{
public:
    /*! Creates the Player
      @param pos start position
     */
    Player(Coord pos) : Unit(pos, Coord(0, 0)), dir(0, -1) {}

    /*! Handles the keyboard events
      @param keyboardState the current state (keys pressed) of the keyboard
     */
    void keyboard(const Uint8* keyboardState) override
    {
        double diff_speed=0.5;

        Coord newDir(0,0);
        
        if (keyboardState[SDL_SCANCODE_UP]) { newDir = Coord(0, -1); }
        if (keyboardState[SDL_SCANCODE_DOWN]) { newDir = Coord(0, 1); }
        if (keyboardState[SDL_SCANCODE_LEFT]) { newDir = Coord(-1, 0); }
        if (keyboardState[SDL_SCANCODE_RIGHT]) { newDir = Coord(1, 0); }

        // update facing direction if movement happens
        if (newDir.x != 0 || newDir.y != 0) { dir = newDir; }

        speed += newDir * diff_speed;
        speed *= 0.95;
    }

    double getRadius() const override { return radius; }

    /*! Draws the Player
      @param mySDL for the size of the window
     */
    void draw(MySDL& mySDL) const override
    {   
        aacircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(255,255,255)); 
        // direction line (visual rotation)
        Coord tip = pos + dir * 50;

        lineColor(
            mySDL.renderer(),
            pos.x, pos.y,
            tip.x, tip.y,
            color(255,255,255)
        );
    }

    Coord getDir() const { return dir; } // 
private:
    static const int radius=24;
    Coord dir;  // facing direction
};

#endif

