
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

            AVector         add( int x, int y ) ;
            AVector         add( AVector * ) ;
            AVector         sub( int x, int y ) ;
            AVector         sub( AVector * ) ;
            AVector         mult( int multiplicand ) ;
            AVector         div( int divisor ) ;
            AVector         setMag( float magnitude ) ;
            AVector         rotate( float theta ) ;
            AVector         fromAngle( float theta ) ;

            float           distance( int x, int y ) const ;
            float           distance( AVector * ) const ;
            float           mag( void ) const ;
            float           heading( void ) const ;
            float           angleBetween( AVector * ) const ;
            float           angleBetween( int x, int y ) const ;
            float           angleBetweenFast( AVector * ) const ;
            float           angleBetweenFast( int x, int y ) const ;
            float           dot( int x, int y ) const ;
            float           dot( AVector * ) const ;

            int             x( void ) const ;
            int             y( void ) const ;
            int             lerp( AVector *, int x ) const ;

            void            set( int x, int y ) ;
            void            set( AVector * ) ;

  unsigned  long            magSq( void ) const ;



private:
            int            _x ;
            int            _y ;

};
