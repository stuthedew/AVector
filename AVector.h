
/**************************************************************************/
/*!
    @file     AVector.h
    @author   Stuart Feichtinger
    @license  MIT (see license.txt)

    Simple library for working with vectors. I got the idea from the
    awesome book The Nature of Code: Simulating Natural Systems with
    Processing by Daniel Shiffman http://natureofcode.com. You can
    download it for free, but it's definitely worth buying!
    (http://www.amazon.com/gp/product/0985930802)


    @section  HISTORY
    v1.0.0 - First release
*/
/**************************************************************************/

#ifndef _AVECTOR_H_
#define _AVECTOR_H_

#include "Arduino.h"
#include <math.h>


class AVector {

public:

  AVector(int x = 0, int y = 0);

  AVector
    set(int x, int y),
    set(AVector *),
    add(int x, int y),
    add(AVector *),
    sub(int x, int y),
    sub(AVector *),
    mult(int),
    div(int),
    setMag(float),
    rotate(float theta),
    fromAngle(float theta);

  float
    distance(int x, int y),
    distance(AVector *),
    mag(),
    heading(),
    angleBetween(AVector *),
    angleBetween(int x, int y),
    dot(int x, int y),
    dot(AVector *);

  int
    x(),
    y();

    unsigned long
      magSq();



private:
  int
    _x,
    _y;

};



#endif
