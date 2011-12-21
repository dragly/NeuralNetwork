#ifndef HELPERS_H
#define HELPERS_H

#include <math.h>

/*!
  Simple random function that returns a uniformly distributed random double.

  @returns Uniformly distributed random number
*/
double ran0() {
    return (double)rand() / (double)RAND_MAX;
}

#endif // HELPERS_H
