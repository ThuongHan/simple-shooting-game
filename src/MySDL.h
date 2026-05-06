#ifndef MYSQL_INCLUDED
#define MYSQL_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Coord.h"

/*!  Holds information about and hides complexity of the SDL2 graphics
  library so we can easily use it to draw. For available draw
  operations see the <a
  href="https://www.ferzkopp.net/Software/SDL_gfx-2.0/Docs/html/_s_d_l__gfx_primitives_8h.html">SDL_gfx
  Primitives</a>.
 */
class MySDL
{
public:

    /*! Creates a graphics window */
    MySDL(std::string title="MyWindow",int width=800,int height=600)
    {
        if (SDL_Init(SDL_INIT_VIDEO)<0)
        { std::cerr<<"SDL, failed to SDL_Init: "<<SDL_GetError()<<'\n';exit(1);}
        if ((_window=SDL_CreateWindow(title.c_str(),
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      width,
                                      height,
                                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE))==NULL)
        { std::cerr<<"SDL, failed to SDL_CreateWindow: "<<SDL_GetError()<<'\n';exit(1);}
        if ((_renderer=SDL_CreateRenderer(_window,-1,SDL_RENDERER_ACCELERATED))==NULL)
        { std::cerr<<"SDL, failed to SDL_CreateRenderer: "<<SDL_GetError()<<'\n';exit(1);}
    }

    /*! Cleans up graphics window resources using the RAII mechanism */
    ~MySDL()
    {
        if (_renderer!=NULL)    SDL_DestroyRenderer(_renderer);
        if (_window!=NULL)      SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    /*! Gets the graphics window to draw in */
    SDL_Window*   window()         { return _window;      }
    
    /*! Gets the renderer used to draw in the graphics window */
    SDL_Renderer* renderer()       { return _renderer;    }

    /*! Gets the current size of the grapics window */
    Coord size() const
    {
        int x,y;
        SDL_GetWindowSize(_window,&x,&y);
        return Coord(x,y);
    }
    
private:
    SDL_Window*      _window=NULL;
    SDL_Renderer*    _renderer=NULL;
};

/*! @file */

/*! \typedef Defines the Color type */
using Color=Uint32;

/*! \fn Makes a color by mixing elements 
  @param red amount of red, valid range [0;255]
  @param green amount of green, valid range [0;255]
  @param blue amount of blue, valid range [0;255]
  @param alpha amount of transparency, valid range [0;255] (0 is fully transparent)
*/
Color color(Uint8 red,Uint8 green,Uint8 blue,Uint8 alpha=255)
{
    Uint8 c[]={red,green,blue,alpha};
    return *((Color*)c);
}

#endif


