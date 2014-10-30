
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
    v1.0.0 - First release
    v1.0.1 - Switched "set" and "setMag" functions to modify calling object
             members, and return void instead of a new AVector object.

*/
/**************************************************************************/



#include "AVector.h"


AVector::AVector(int x, int y){
  _x = x;
  _y = y;
}

int AVector::x(){

  return _x;
}

int AVector::y(){

  return _y;
}

AVector AVector::add(int x, int y){
  AVector rV(_x+x, _y+y);

  return rV;
}

AVector AVector::add(AVector *v){
  AVector rV(_x + v->x(), _y + v->y());

  return rV;
}

AVector AVector::sub(int x, int y){
  AVector rV(_x - x, _y - y);

  return rV;
}

AVector AVector::sub(AVector *v){
  AVector rV(_x - v->x(), _y - v->y());

  return rV;
}

void AVector::set(int x, int y){
  _x = x;
  _y = y;

}

void AVector::set(AVector *v){
  set(v->x(), v->y());
}

AVector AVector::mult(int val){
  AVector rV(_x * val, _y * val);

  return rV;
}

AVector AVector::div(float val){
  AVector rV(round(_x / val), round(_y / val));

  return rV;
}

float AVector::distance(int x, int y){

  return sqrt(pow((x - _x), 2) + pow((y - _y),2));
}

float AVector::distance(AVector *v){

  return distance(v->x(), v->y());
}

float AVector::mag(){

  return sqrt(magSq());
}

unsigned long AVector::magSq(){
  unsigned long x = _x;
  unsigned long y = _y;
  return (x*x + y*y);
}

float AVector::dot(int x, int y){
  return (_x*x + _y*y);
}

float AVector::dot(AVector *v){
  return dot(v->x(), v->y());
}

float AVector::heading(){
  return -1*atan2(-1*_y, _x);
}

void AVector::setMag(float newMag){
  AVector  rV = mult(newMag);
  rV = rV.div(mag());
  set(&rV);
}

AVector AVector::fromAngle(float theta){
  AVector rV(round(cos(theta)*100), round(sin(theta)*100));
  return rV;
}

float AVector::angleBetween(AVector *v){
  // We get NaN if we pass in a zero vector which can cause problems
  // Zero seems like a reasonable angle between a (0,0) vector and something else
  if (_x == 0 && _y == 0) return 0;
  if (v->x() == 0 && v->y() == 0) return 0;

  // This should be a number between -1 and 1, since it's "normalized"
  float amt = dot(v) / (mag() * v->mag());
  /*
  Serial.println(dot(v));
  Serial.println(mag());
  Serial.println(v->mag());
  Serial.println(amt);
  Serial.println(acos(amt)*180 / M_PI);
  */
  // But if it's not, due to rounding error, then we need to fix it
  // http://code.google.com/p/processing/issues/detail?id=340
  // Otherwise if outside the range, acos() will return NaN
  // http://www.cppreference.com/wiki/c/math/acos
  if (amt <= -1) {
    return M_PI;
  } else if (amt >= 1) {

    return 0;
  }
  return acos(amt);
}

float AVector::angleBetween(int x, int y){
  AVector rV(x, y);
  return angleBetween(&rV);
}

AVector AVector::rotate(float theta){
  int temp = _x;
  AVector rV(round(_x * cos(theta) - _y*sin(theta)), round(temp*sin(theta) + _y * cos(theta)));

  return rV;
}
