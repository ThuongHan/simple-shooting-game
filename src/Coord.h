#ifndef COORD_INCLUDED
#define COORD_INCLUDED

/*!
  Coordinate x,y used for things like size, position and speed.
 */
struct Coord
{
    double x,y;

    Coord() : x{0},y{0}
    {}
    
    Coord(double x,double y) : x{x},y{y}
    {}

    Coord& operator+=(const Coord& c)
    { x+=c.x; y+=c.y; return *this; }
    
    Coord operator+(const Coord& c) const
    { Coord n=*this; return n+=c; }

    Coord& operator*=(double d)
    { x*=d; y*=d; return *this; }

    Coord operator*(double d) const
    { Coord n=*this; return n*=d; }
    
    Coord operator-() const
    { Coord n=*this; n.x=-n.x; n.y=-n.y; return n; }
};

#endif

