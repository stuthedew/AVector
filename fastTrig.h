

/**************************************************************************/
/*!
    @file     fastTrig.h
    @author   Stuart Feichtinger
    @license  MIT (see license.txt)

    My attempts to speed up the trig functions I need.


    @section  HISTORY
    v0.0.1 - First release
*/
/**************************************************************************/

#ifndef _FASTTRIG_H_
#define _FASTTRIG_H_

#include "Arduino.h"
#include <avr/pgmspace.h>

#define LOOKUP_SIZE 9


const uint16_t acos_lookup[][2] PROGMEM = {{0, 90}, {35, 88}, {358, 69}, {720, 44}, {93, 23},
                  {94, 20}, {97, 14}, {99,8}, {1000, 0}};



typedef struct sPoint_t {
  const int
    x,
    y;

    sPoint_t(int _x, int _y):x(_x), y(_y){}
};




float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//      y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}


int searchLookupTable(int target, const uint16_t (*lookUpTable)[2], int tableSize){
  int i;
  int bestIndex;
  for(i=0; i<tableSize; i++){/*
    Serial.print(pgm_read_byte_near(&(lookUpTable[i][0])));
    Serial.print(F(", "));
    Serial.println(pgm_read_byte(&(lookUpTable[i][1])));
    */
    if(target > pgm_read_byte_near(&(lookUpTable[i][0]))){
      //Serial.println(pgm_read_byte_near(lookUpTable + i*2 + 1));
      bestIndex = i;
    }
    else{
      return bestIndex;
    }
  }
  return bestIndex;
}


inline uint16_t _bLkup(const uint16_t (*lTable)[2], uint8_t i1, uint8_t i2){
  return pgm_read_byte(&(lTable[i1][i2]));
}

uint8_t lerp(int index, const uint16_t (*lTable)[2], int x){
  uint8_t y;
  float tmp;
  /*
  tmp = (x - pgm_read_byte(&(lTable[index][0])));
  tmp *= (pgm_read_byte(&(lTable[index][1])) - pgm_read_byte(&(lTable[index + 1][1])));
  tmp /= (pgm_read_byte(&(lTable[index][0])) - pgm_read_byte(&(lTable[index + 1][0])));
  y = pgm_read_byte(&(lTable[index][1]))+round(tmp);
  */
  tmp = x - _bLkup(lTable, index, 0);
  tmp *= _bLkup(lTable, index, 1) - _bLkup(lTable, index + 1, 1);
  tmp /= (_bLkup(lTable, index, 0) - _bLkup(lTable, index + 1, 0));
  y = _bLkup(lTable, index, 1);+round(tmp);

  //Serial.print(F("y: "));
  //Serial.println(y);
  return(y);
}

int fast_acos(float val){
  int sign;
  (val > 0) ? sign = 1 : sign = -1;

  int lVal = sign*1000*val; // scale value to change to int
  lVal -= 1000; //adjust correction value based on sign

  int index = searchLookupTable(lVal, acos_lookup, LOOKUP_SIZE);

  //Serial.println(F("index"));
  //Serial.println(index);

  // adjust if val is outside the lookup table
  (index + 1 >= LOOKUP_SIZE) ? index -= 1 : index;

  if(sign > 0){
    return lerp(index, acos_lookup, lVal);
  }
  else{
  return 180 - lerp(index, acos_lookup, lVal);
  }

}

#endif
