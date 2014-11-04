

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



#include <stddef.h>

// Stuff that is normally provided by Arduino
#ifdef ARDUINO

#if ARDUINO > 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#else
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#endif

// Avoid spurious warnings
#if 1
#if ! defined( NATIVE ) && defined( ARDUINO )
#undef PROGMEM
#define PROGMEM __attribute__(( section(".progmem.data") ))
#undef PSTR
#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))
#endif
#endif

// Progmem is Arduino-specific
#ifdef ARDUINO
#include <avr/pgmspace.h>
#define PRIPSTR "%S"
#else
typedef char const char;
typedef uint16_t prog_uint16_t;
#define PSTR(x) (x)
#define printf_P printf
#define strlen_P strlen
#define PROGMEM
#define pgm_read_word(p) (*(p))
#define PRIPSTR "%s"
#endif

#define LOOKUP_SIZE 16


const int16_t acos_lookup[][2] PROGMEM = {
                    {0, 90}, {17, 89}, {35, 88}, {105, 84},
                    {208, 78}, {358, 69}, {407, 66}, {530, 58},
                    {720, 44}, {819, 35}, {883, 28}, {920, 23},
                    {940, 20}, {970, 14}, {990,8}, {999, 0}};


double Q_rsqrt( double number )
{
	long i;
	double x2, y;
	const double threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil doubleing point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( double * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
  //y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}


int searchLookupTable(int target, const int16_t (*lookUpTable)[2], int tableSize){
  int i;
  int bestIndex = 0;
  for(i=0; i<tableSize; i++){
    /*
    Serial.print(pgm_read_word_near(&(lookUpTable[i][0])));
    Serial.print(F(", "));
    Serial.println(pgm_read_word(&(lookUpTable[i][1])));
    */
    if(target > pgm_read_word_near(&(lookUpTable[i][0]))){
      //Serial.println(pgm_read_word_near(lookUpTable + i*2 + 1));
      bestIndex = i;
    }
    else{
      return bestIndex;
    }
  }
  return bestIndex;
}


inline uint16_t _memRead(const int16_t (*lTable)[2], uint8_t i1, uint8_t i2){
  return pgm_read_word(&(lTable[i1][i2]));
}

uint16_t lerp(int index, const int16_t (*lTable)[2], int16_t x){
  int16_t y;
  int64_t tmp;

  tmp = x - _memRead(lTable, index, 0);

  tmp *= (int)(_memRead(lTable, index + 1, 1) - _memRead(lTable, index, 1));

  tmp /= (_memRead(lTable, index + 1, 0) - _memRead(lTable, index, 0));

  y = _memRead(lTable, index, 1) + tmp;
  /*
  Serial.print(tmp);
  Serial.print(F(", "));
  Serial.print(y);
  Serial.print(F(", "));
  Serial.print(index);
  Serial.print(F(", "));
  Serial.println(_memRead(lTable, index, 1));
*/

  return(y);
}

int fast_acos(double val){
  int sign;
  (val > 0) ? sign = 1 : sign = -1;

  int lVal = sign*1000*val; // scale value to change to int
  //Serial.println(lVal);

  int index = searchLookupTable(lVal, acos_lookup, LOOKUP_SIZE);
/*
  Serial.println(F("index"));
  Serial.println(index);
*/
  // adjust if val is outside the lookup table
  (index + 1 < LOOKUP_SIZE) ? index -= 1 : index;

//  Serial.println(F("Adjusted index"));
  //Serial.println(index);

  if(sign > 0){
    return lerp(index, acos_lookup, lVal);
  }
  else{
  return 180 - lerp(index, acos_lookup, lVal);
  }

};

#endif
