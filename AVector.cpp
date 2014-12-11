
/**************************************************************************/
/*!
    @file     AVector.cpp
    @author   Stuart Feichtinger
    @license  MIT (see license.txt)

    Simple library for working with vectors based on processing
    (processing.org). I got the idea from the awesome book: "The Nature of
    Code: Simulating Natural Systems with Processing" by Daniel Shiffman
    (http://natureofcode.com). You can download it for free from his
    website, but it's definitely worth buying!
    (http://www.amazon.com/gp/product/0985930802)


    @section  HISTORY
    v0.0.1 - First release

*/
/**************************************************************************/



#include "AVector.h"
#include "fastTrig.h"


AVector::AVector( int x, int y ) {
  _x = x;
  _y = y;
}

int AVector::x( void ) const {

  return _x;
}

int AVector::y( void ) const {

  return _y;
}

AVector AVector::add( int x, int y ) {
  AVector returnVector(_x+x, _y+y) ;

  return returnVector;
}

AVector AVector::add( AVector *v ) {
  AVector returnVector(_x + v->x(), _y + v->y()) ;

  return returnVector;
}

AVector AVector::sub( int x, int y ) {
  AVector returnVector(_x - x, _y - y) ;

  return returnVector;
}

AVector AVector::sub( AVector *v ) {
  AVector returnVector(_x - v->x(), _y - v->y()) ;

  return returnVector;
}

void AVector::set( int x, int y ) {
  _x = x;
  _y = y;


}

void AVector::set( AVector *v ) {
  _x = v->x() ;
  _y = v->y() ;
}

AVector AVector::mult( int val ) {
  AVector returnVector(_x * val, _y * val) ;

  return returnVector;
}

AVector AVector::div( int val ) {
  AVector returnVector(round(_x / val), round(_y / val)) ;

  return returnVector ;
}

float AVector::distance( int x, int y ) const {

  return sqrt( pow( ( x - _x ), 2 ) + pow( ( y - _y ), 2) ) ;
}

float AVector::distance( AVector *v ) const {

  return distance(v->x(), v->y()) ;
}

float AVector::mag( void ) const {

  return sqrt(magSq()) ;
}

float AVector::mag( int x, int y ) const {

  return sqrt(magSq(x, y)) ;
}

unsigned long AVector::magSq( void ) const {
  return (_x*_x + _y*_y) ;
}

unsigned long AVector::magSq( int x, int y ) const {
  return ( x*x + y*y ) ;
}

float AVector::dot( int x, int y ) const {
  return ( _x*x + _y*y ) ;
}

float AVector::dot( AVector *v ) const {
  return dot( v->x(), v->y() ) ;
}

float AVector::heading( void ) const {
  return -1 * atan2( -1*_y, _x ) ;
}

AVector AVector::setMag( float newMag ) {
  float temp = mag() ;
  AVector returnVector = mult( newMag ) ;
  return returnVector.div( temp ) ;
}

AVector AVector::fromAngle( float theta ) {
  AVector returnVector( round( cos( theta )*100 ), round( sin( theta )*100 ) ) ;
  return returnVector ;
}

float AVector::angleBetween( int x, int y ) const {
  // We get NaN if we pass in a zero vector which can cause problems
  // Zero seems like a reasonable angle between a (0,0) vector and something else
  if (_x == 0 && _y == 0) return 0 ;
  if ( x == 0 && y == 0) return 0 ;

  // This should be a number between -1 and 1, since it's "normalized"
  float amt = dot( x, y ) / (mag() * mag( x, y )) ;

  #ifdef SLOW_DEBUG
  Serial.println(dot(x, y)) ;
  Serial.println(mag()) ;
  Serial.println(mag(x, y)) ;
  Serial.println(amt) ;
  Serial.println(acos(amt)*180 / M_PI) ;
  #endif
  // But if it's not, due to rounding error, then we need to fix it
  // http://code.google.com/p/processing/issues/detail?id=340
  // Otherwise if outside the range, acos() will return NaN
  // http://www.cppreference.com/wiki/c/math/acos
  if (amt <= -1) {
    return M_PI;
  } else if (amt >= 1) {

    return 0;
  }

  return acos(amt) ;

}

float AVector::angleBetweenFast( int x, int y ) const {
  // We get NaN if we pass in a zero vector which can cause problems
  // Zero seems like a reasonable angle between a (0,0) vector and something else
  if (_x == 0 && _y == 0) return 0;
  if ( x == 0 && y == 0) return 0;
  // This should be a number between -1 and 1, since it's "normalized"
  float amt = dot( x, y ) * invSqrt( magSq() * magSq(x, y) ) ;

  #ifdef FAST_DEBUG
  Serial.println(dot(v)) ;
  Serial.println(mag()) ;
  Serial.println(mag(x, y)) ;
  Serial.println(amt) ;
  Serial.println(acos(amt)*180 / M_PI) ;
  #endif
  // But if it's not, due to rounding error, then we need to fix it
  // http://code.google.com/p/processing/issues/detail?id=340
  // Otherwise if outside the range, acos() will return NaN
  // http://www.cppreference.com/wiki/c/math/acos
  if (amt <= -1) {
    return M_PI;
  } else if (amt >= 1) {
    return 0;
  }
  return fast_acos( amt ) ;
}

float AVector::angleBetween( AVector *v ) const {
  return angleBetween( v->x(), v->y() ) ;
}

float AVector::angleBetweenFast( AVector *v ) const {
  return angleBetweenFast( v->x(), v->y() ) ;
}

AVector AVector::rotate( float theta ) {
  int temp = _x;
  AVector returnVector(round(_x * cos(theta) - _y*sin(theta)), round(temp*sin(theta) + _y * cos(theta))) ;
  return returnVector ;
}

int AVector::lerp( AVector *v, int tX ) const {
  return fast_acos( 1.42 ) ;
  int16_t tY ;
  int32_t tmp ;
  tmp = ( tX - x() ) ;
  tmp *= ( v->y() - y() ) ;
  tmp /= ( v->x() - x() ) ;
  tY = y() + tmp;
  return( tY ) ;

}
