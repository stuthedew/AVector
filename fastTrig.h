

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


typedef struct sPoint_t {
  const int
    x,
    y;

    sPoint_t(int _x, int _y):x(_x), y(_y){}
};

prog_uchar acos_lookup[][2] PROGMEM = {{0, 90}, {1, 89}, {72, 44}, {73, 43}, {93, 23},
                  {94, 20}, {97, 14}, {99,8}, {100, 0}};




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



int searchLookupTable(int target, prog_uchar (*lookUpTable)[2], int tableSize){
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


uint8_t lerp(int index, prog_uchar (*lookUpTable)[2], int x){
uint8_t y;
int16_t tmp;
tmp = (x - pgm_read_byte(&(lookUpTable[index][0])));
tmp *= (pgm_read_byte(&(lookUpTable[index][1])) - pgm_read_byte(&(lookUpTable[index + 1][1])));
tmp /= (pgm_read_byte(&(lookUpTable[index][0])) - pgm_read_byte(&(lookUpTable[index + 1][0])));
y = pgm_read_byte(&(lookUpTable[index][1]))+tmp;
//Serial.print(F("y: "));
//Serial.println(y);
return(y);
}

int fast_acos(float val){
  int lVal = 100*val;
  lVal -= 100;

  int index = searchLookupTable(lVal, acos_lookup, 9);
  //Serial.println(F("index"));
  //Serial.println(index);
  return lerp(index, acos_lookup, lVal);
}

#endif
