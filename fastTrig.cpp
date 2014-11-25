

/**************************************************************************/
/*!
    @file     fastTrig.cpp
    @author   Stuart Feichtinger
    @license  MIT (see license.txt)

    My attempts to speed up the trig functions I need.


    @section  HISTORY
    v0.0.1 - First release

*/
/**************************************************************************/

#include "fastTrig.h"


//Adapted from "FAST INVERSE SQUARE ROOT" paper by Chris Lomont
//<http://www.lomont.org/Math/Papers/2003/InvSqrt.pdf>
float invSqrt( float number ){

  float xhalf = 0.5f * number ;
  float y = number ;
  int i = *( int* )&y ;                 // get bits for floating value
  i = 0x5f3759df - ( i>>1 ) ;           // gives initial guess y0
  y = *( float* )&i ;                   // convert bits back to float
//y = y * ( 1.5f - xhalf * y * y ) ;    // Newton step, repeating increases accuracy

	return y;
}


int searchLookupTable( int target, const int16_t ( *lookUpTable )[2], int tableSize ){
  int i;
  int bestIndex = 0;
  for( i=0; i<tableSize; i++ ){

    #ifdef FAST_TRIG_DEBUG
      Serial.print(pgm_read_word_near( &( lookUpTable[i][0] ) ) );
      Serial.print(F(", "));
      Serial.println(pgm_read_word( &( lookUpTable[i][1] ) ) );
    #endif

    if(target > pgm_read_word_near( &( lookUpTable[i][0] ) ) ){
      //Serial.println(pgm_read_word_near(lookUpTable + i*2 + 1));
      bestIndex = i;
    }
    else{
      return bestIndex;
    }
  }
  return bestIndex;
}


uint16_t lerp( int16_t x, int index, const int16_t ( *lTable )[2] ){
  int16_t y ;
  int64_t tmp ;

  tmp = x - _memRead( lTable, index, 0 ) ;

  tmp *= (int)(_memRead( lTable, index + 1, 1 ) - _memRead( lTable, index, 1 ) ) ;

  tmp /= ( _memRead( lTable, index + 1, 0 ) - _memRead( lTable, index, 0 ) ) ;

  y = _memRead( lTable, index, 1 ) + tmp;

  #ifdef FAST_TRIG_DEBUG
    Serial.println( F( "MEM READ" ) );
    Serial.print(tmp);
    Serial.print(F(", "));
    Serial.print(y);
    Serial.print(F(", "));
    Serial.print(index);
    Serial.print(F(", "));
    Serial.println( _memRead( lTable, index, 1 ) );
  #endif

  return( y ) ;
}


int fast_acos( double val ){
  int sign ;
  ( val > 0 ) ? sign = 1 : sign = -1 ; // determine if negative number

  int lVal = sign*1000*val; // scale value to change to int
  //Serial.println(lVal);

  int index = searchLookupTable(lVal, acos_lookup, LOOKUP_SIZE);
/*
  Serial.println(F("index"));
  Serial.println(index);
*/

  (index + 1 < LOOKUP_SIZE) ? index -= 1 : index; // adjust if val is outside the lookup table

//  Serial.println(F("Adjusted index"));
  //Serial.println(index);

  if( sign > 0 ){
    return lerp( lVal, index, acos_lookup );
  }
  else{
  return 180 - lerp( lVal, index, acos_lookup );
  }

}
