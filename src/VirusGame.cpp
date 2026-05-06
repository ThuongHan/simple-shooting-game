
#include "Utils.h"
#include "MySDL.h"
#include "Coord.h"
#include "Player.h"
#include "Virus.h"
#include "Unit.h"
#include "Bullet.h"
#include "BigVirus.h"
#include <vector>
#include <memory>
#include <algorithm>

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

// Time (ms) when the last bullet was fired
int lastBulletTime = 0;
// minimum delay between shots -> 3 bullets perseconds is about 333 ms
const int bulletCooldown = 333;

// Initial score always is 10
int score = 10; 
const int winningScore = 20;

// Represent the current state of the game and track it
enum class gameState {Playing, Won, Lost};
gameState state = gameState::Playing;


void handleEvents(bool& quit)
{
    SDL_Event e;
    while( SDL_PollEvent(&e) ) // handle events
    {
        int x, y;
        switch(e.type)
        {
        case SDL_QUIT:
            quit = true; break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState( &x, &y );
            std::cout<<"mouse down: "<<x<<","<<y<<'\n';
            break;
        }
        
    }
}

void spawnVirus(std::vector< std::unique_ptr<Unit> >& units,
                MySDL& mySDL,
                double new_virus_chance,
                double new_virus_max_speed,
                int max_nr_units)
{
    if (units.size() >- max_nr_units) return;
    Coord window_size=mySDL.size();
    Coord pos  = Coord(window_size.x       * rand_0_1() ,  window_size.y       * rand_0_1() );
    Coord speed= Coord(new_virus_max_speed * rand_m1_1(),  new_virus_max_speed * rand_m1_1());

    if (rand_0_1() < new_virus_chance) {units.push_back(std::make_unique<Virus>(pos, speed));}
    if (rand_0_1() < new_virus_chance * 0.9) {units.push_back(std::make_unique<BigVirus>(pos, speed));}
}

void updateUnits(std::vector< std::unique_ptr<Unit> >& units,
                 const Uint8* keyboardState,
                 MySDL& mySDL)
{
    std::for_each(units.begin(), units.end(),
                  [&](auto& unit)
                  {
                    unit->keyboard(keyboardState);
                    unit->step(mySDL);
                    unit->draw(mySDL);
                  });    
}

bool intersection(const Unit& unit1, const Unit& unit2)
{
    Coord distance = Coord(unit1.getPos().x - unit2.getPos().x,
                           unit1.getPos().y - unit2.getPos().y); // Distance from both centers
    double distance2 = distance.x * distance.x          
                       + distance.y * distance.y;
    double totalRadius = unit1.getRadius() + unit2.getRadius();
    return distance2 < totalRadius * totalRadius;
}

// Here I am checking every pair of objects in the game and decide 
// what happens during collision. For each pair I need to figure out
// whether they are a bullet, a virus (normal or big), or a player
// for which i use dynamic_cast since everything is stored as unit 
void handleCollisions(std::vector<std::unique_ptr<Unit>>& units)
{
    for (int i = 0; i < (int)units.size(); i++)
    {
        if (units[i]->isDead()) continue;

        for (int j = i + 1; j < (int)units.size(); j++)
        {
            if (units[j]->isDead()) continue;
            if (!intersection(*units[i], *units[j])) continue;

            Unit* a = units[i].get();
            Unit* b = units[j].get();

            Bullet* bullet = dynamic_cast<Bullet*>(a);
            if (!bullet) { bullet = dynamic_cast<Bullet*>(b); }

            Virus* virus = dynamic_cast<Virus*>(a);
            if (!virus) { virus = dynamic_cast<Virus*>(b); }

            Player* player = dynamic_cast<Player*>(a);
            if (!player) { player = dynamic_cast<Player*>(b); }

            // Bullet collision with virus and big virus
            if (bullet && (virus || dynamic_cast<BigVirus*>(a) || dynamic_cast<BigVirus*>(b)))
            {
                BigVirus* big = dynamic_cast<BigVirus*>(a);
                if (!big) big = dynamic_cast<BigVirus*>(b);

                bullet->kill();

                if (big)
                {
                    big->hit();
                    if (big->isDead())
                        score += big->scoreValue();
                }
                else if (virus)
                {
                    virus->kill();
                    score += virus->scoreValue();
                }

                continue;
            }

            // Player collision with virus and big virus
            BigVirus* big = dynamic_cast<BigVirus*>(a);
            if (!big) big = dynamic_cast<BigVirus*>(b);

            virus = dynamic_cast<Virus*>(a);
            if (!virus) virus = dynamic_cast<Virus*>(b);

            if (player && (virus || big))
            {
                if (big)
                {
                    big->hit();
                    if (big->isDead())
                        score -= big->scoreValue(); // Lose 2 scores when hit with bigVirus
                }
                else if (virus)
                {
                    virus->kill();
                    score--;    // Lose 1 score when hit with normal virus
                }
            }
        }
    }
}

void eraseDeadUnits(std::vector< std::unique_ptr<Unit> >& units)
{
    units.erase(std::remove_if(units.begin(), units.end(),
                [](const std::unique_ptr<Unit>& unit)
                {
                    return unit->isDead();
                }), units.end() );
}

void updateGameState()
{
    if (state != gameState::Playing)
        return;
    
    if (score >= winningScore)
    {
        state = gameState::Won;
        std::cout << "You won!\n";
    }
    else if (score < 0)
    {
        state = gameState::Lost;
        std::cout << "You lost!\n";
    }
}


/*! @file
   The starting point of VirusGame, holds the main() function.
*/
extern "C" int main(int argc, char* argv[])
{
    std::cout<<"Use the cursor keys to move around\n";
    srand(time(NULL));        // seed the speudo random number generator 
    MySDL mySDL("VirusGame"); // create an SDL graphics window
    
    const int max_nr_units=20;    // maximum number of units, feel free to change

    std::vector< std::unique_ptr<Unit> > units;    // Vector container holding all units in the game
    units.push_back(std::make_unique<Player>(mySDL.size() * 0.5));    // Add player to units container, (deallocation handled automatically)

    double new_virus_chance=0.009; // the chance that a new virus is created each time step
    double new_virus_max_speed=3; // maximum speed of a new virus
    
    bool quit=false;
    while (!quit) // the game loop, this loops has gotten large, better split it up in multiple functions?
    {
        int ticks_start=SDL_GetTicks();
        SDL_SetRenderDrawColor(mySDL.renderer(),0,0,0,255); // black background
        SDL_RenderClear(mySDL.renderer()); // clear graphics window

        handleEvents(quit);

        const Uint8* keyboardState=SDL_GetKeyboardState(NULL); // get keyboard state
        
        if (state == gameState::Playing)
        {
            // Shooting
            Player* player = dynamic_cast<Player*>(units[0].get()); // Downcasting to verify Unit type
            if (player && keyboardState[SDL_SCANCODE_SPACE])
            {
                int currentTime = SDL_GetTicks();
                if (currentTime - lastBulletTime >= bulletCooldown)
                {
                    units.push_back(std::make_unique<Bullet>(
                                player->getPos() + player->getDir() * 30.0,
                                player->getDir() * 10.0
                                ));
                    lastBulletTime = currentTime;
                }
            }

            spawnVirus(units, mySDL, new_virus_chance,
                    new_virus_max_speed, max_nr_units);
            
            updateUnits(units, keyboardState, mySDL);

            handleCollisions(units);

            eraseDeadUnits(units);

            updateGameState();
        }


        // Show if win/lose
        if(state == gameState::Won) { stringColor(mySDL.renderer(), 300, 300,
                                                 "You won!",
                                                 color(255,255,0)); }

        else if (state == gameState::Lost) { stringColor(mySDL.renderer(), 300, 300,
                                                 "You lost!",
                                                 color(255,255,0)); }  

        // Show score
        std::string text = "Score: " + std::to_string(score);
        stringColor(mySDL.renderer(), 10, 10, text.c_str(), color(255,255,255));

        SDL_RenderPresent(mySDL.renderer()); // update graphics window
        int frame_ticks=SDL_GetTicks()-ticks_start;
        if( frame_ticks < SCREEN_TICKS_PER_FRAME ) SDL_Delay( SCREEN_TICKS_PER_FRAME - frame_ticks ); // delay for right framerate
    }

    return 0;
}




