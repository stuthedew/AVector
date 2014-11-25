

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

#pragma once

#include <avr/pgmspace.h>


#define LOOKUP_SIZE 16


typedef struct divisor_t {
  const int16_t *multiplicand ;
  const uint8_t *shift ;

  divisor_t( int16_t* const m, uint8_t* const s ):multiplicand( m ),shift( s ){}

} divisor_t;


const int16_t acos_lookup[][2] PROGMEM = {
  { 0  , 90 },  { 17, 89  },  { 35 , 88 },  { 105, 84 },
  { 208, 78 },  { 358, 69 },  { 407, 66 },  { 530, 58 },
  { 720, 44 },  { 819, 35 },  { 883, 28 },  { 920, 23 },
  { 940, 20 },  { 970, 14 },  { 990, 8  },  { 999, 0  }
} ;


/// Get inverse square root of number using fast inverse square root algorithm
/// made popular by Quake 3.
///
///@param number Number from which to calculate the inverse square root.
///@return The inverse square root of input number.

float Q_rsqrt( float number ) ;


/// Get lookup table index for known x values above and below target x value for
/// subsiquent interpolation.
///
///@param target The x value to bracket
///@param lookUpTable The lookup table to search
///@param tableSize The number of known reference values in lookup table.
///@return The index of the reference x value below target. (Higher = index + 1)

int searchLookupTable( int target, const int16_t ( *lookUpTable )[2], int tableSize ) ;


        uint16_t  lerp( int index, const int16_t ( *lTable )[2], int16_t x ) ;
        int       fast_acos( double val ) ;
        int       fast_acos( double val ) ;

/// Read from acos lookup table stored in flash memory (PROGMEM).
/// Helper function not meant to be called by user. Use "searchLookupTable"
/// instead.
///
///@param lTable The table to read from.
///@param set set to read from
///@param var variable to read (x or y)
///@return The desired value from table.

inline  uint16_t  _memRead( const int16_t ( *lTable )[2], uint8_t set, uint8_t var ){ return pgm_read_word( &( lTable[set][var] ) ); }
