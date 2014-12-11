
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
    v0.0.1 - First release
*/
/**************************************************************************/

#pragma once

#include "Arduino.h"
#include <math.h>


class AVector {

public:

  AVector( int x = 0, int y = 0 ) ;

  AVector
    add( int x, int y ) ,
    add( AVector * ) ,
    sub( int x, int y ) ,
    sub( AVector * ) ,
    mult( int multiplicand ) ,
    div( int divisor ) ,
    setMag( float magnitude ) ,
    rotate( float theta ) ,
    fromAngle( float theta ) ;

  float
    distance( int x, int y ) const,
    distance( AVector * ) const,
    mag( void ) const ,
    mag( int x, int y ) const ,
    heading( void ) const,
    angleBetween( AVector * ) const ,
    angleBetween( int x, int y ) const ,
    angleBetweenFast( AVector * ) const ,
    angleBetweenFast( int x, int y ) const ,
    dot( int x, int y ) const ,
    dot( AVector * ) const ;



  int
    x( void ) const ,
    y( void ) const ,
    lerp( AVector *, int x ) const ;

  void
    set( int x, int y ) ,
    set( AVector * ) ;

  unsigned long
    magSq( void ) const ,
    magSq( int x, int y ) const ;



private:
  int
    _x ,
    _y ;

};
