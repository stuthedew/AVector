

/**************************************************************************/
/*!
@file     fastTrig.h
@author   Stuart Feichtinger
@license  MIT (see license.txt)

My attempts to speed up the trig functions I need.


@section  HISTORY
v0.0.1 - First release
v0.0.2 - Added a corresponding cpp file.
v0.0.3 - Added documentation.
*/
/**************************************************************************/

#pragma once

#include <avr/pgmspace.h>

#define LOOKUP_SIZE 16


/// Lookup table for acos calculation.
/// x = angle in degrees between 0 and 90 multiplied by 1000
/// y = acos value.

const int16_t acos_lookup[][2] PROGMEM = {
  { 0  , 90 },  { 17, 89  },  { 35 , 88 },  { 105, 84 },
  { 208, 78 },  { 358, 69 },  { 407, 66 },  { 530, 58 },
  { 720, 44 },  { 819, 35 },  { 883, 28 },  { 920, 23 },
  { 940, 20 },  { 970, 14 },  { 990, 8  },  { 999, 0  }
} ;



/// Multiplication/bit shift pair to avoid floats if possible.
/// e.g.
///   pi ~= 3.14 ~= 22/7
///   Find a power of 2 that is close to a multiple of 7 (bit shifts are cheap)
///   7*73 = 511 ~= 512 = 2^9
///   Float Value   Calculated    Difference from pi
///   -----------   ----------    ---------------------
///        pi        3.1416           0%
///      22 / 7      3.1429          0.04%
///   (22*73) >> 9   3.1367          0.16%

typedef struct divisor_t {
  const int16_t *multiplicand ;
  const uint8_t *shift ;

  divisor_t( int16_t* const m, uint8_t* const s ):multiplicand( m ),shift( s ){}

} divisor_t;


/// Get inverse square root of number using fast inverse square root algorithm
/// made popular by Quake 3.
///
/// @param number Number from which to calculate the inverse square root.
/// @return The inverse square root of input number.

float Q_rsqrt( float number ) ;


/// Get lookup table index for known x values above and below target x value for
/// subsiquent interpolation.
///
/// @param target The x value to bracket
/// @param lookUpTable The lookup table to search (PROGMEM)
/// @param tableSize The number of known reference values in lookup table.
/// @return The index of the reference x value below target. (Higher = index + 1)

int searchLookupTable( int target, const int16_t ( *lookUpTable )[2], int tableSize ) ;


/// Calculate y value from x input using linear interpolation of a lookup table.
///
/// @param x The x value input used to calculate y
/// @param index The lower index value of lookup table (given by "serchLookupTable"
/// function)
/// @param lTable The lookup table to search (PROGMEM)
/// @return The y value calculated by linear interpolation

uint16_t lerp( int16_t x, int index, const int16_t ( *lTable )[2] ) ;


/// Main function meant to be called by user. Provides fast acos calculation
/// using a lookup table and interpolation.
///
/// @param val Value from which to calcute acos.
/// @return Calculated acos angle (in degrees).

int fast_acos( double val ) ;


/// Read from acos lookup table stored in flash memory (PROGMEM).
/// Inline to increase spead.
/// Helper function not meant to be called by user. Use "searchLookupTable"
/// instead.
///
/// @param lTable The table to read from.
/// @param set set to read from
/// @param var variable to read (x or y)
/// @return The desired value from table.

inline uint16_t _memRead( const int16_t ( *lTable )[2], uint8_t set, uint8_t var ){ return pgm_read_word( &( lTable[set][var] ) ); }
