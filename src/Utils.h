#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <stdlib.h>
#include <time.h>
#include <iostream>

/*! @file 
  Some useful helper functions.
*/

/*! Generate random number in range [0;1]  */
double rand_0_1()
{  return rand()/static_cast<double>(RAND_MAX); }

/*! Generate random number in range [-1;+1]  */
double rand_m1_1()
{  return rand_0_1()*2-1; }

#endif

