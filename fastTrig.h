

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
/// [][0] = angle in degrees between 0 and 90 multiplied by 1000
/// [][1] = acos value.

const int16_t acos_lookup[][2] PROGMEM = {
  {   0, 90 },  {  17, 89 },  {  35, 88 },  { 105, 84 },
  { 208, 78 },  { 358, 69 },  { 407, 66 },  { 530, 58 },
  { 720, 44 },  { 819, 35 },  { 883, 28 },  { 920, 23 },
  { 940, 20 },  { 970, 14 },  { 990,  8 },  { 999,  0 }
} ;


/// Multiplication/bit shift pair to avoid floats if possible.
/// e.g.
///   pi ~= 3.14 ~= 22/7
///   Find a power of 2 that is close to a multiple of 7 (bit shifts are cheap)
///   7*73 = 511 ~= 512 = 2^9


typedef struct divisor_t {
  int16_t multiplicand ;
  uint8_t shift ;

} divisor_t;


/// Lookup table for linear interpolation divisor between points on acos
/// lookup table using multiplication and shift. =~ 1/(x2 - x1)
/// [][0] = Multiplicand.
/// [][1] = Shift value.
///
/// e.g.
///   slope = (y2 - y1) / (x2 - x1)<< evil repeating division
///   (x1, y1) = acos_lookup[0] = (0, 90)
///   (x2, y2) = acos_lookup[1] = (17, 89)
///
///   {Multiplicand} *Shift value*
///   17 * {15} = 255 ~= 256 = 2^*9*
///   (89 - 90)/(17 - 0) ~= ((val * {15}) >> *9*)
///
///       val         val /         Difference acutal
///   -----------   ----------    ---------------------
///        2        3.1416                 0%
///        8        3.1429                0.04%
///       12        3.1367                0.16%

const divisor_t DIVISOR_TABLE[] PROGMEM = {

// { Mult, shift }
// for 1/(x2 - x1) used in lerp function (linear interpolation)

  { 15 ,  8 },        // x2 = acos_lookup[1][0]   x1 = acos_lookup[0][0]
{ 57 , 10 },        // x2 = acos_lookup[2][0]   x1 = acos_lookup[1][0]
  { 117 , 13 },        // x2 = acos_lookup[3][0]   x1 = acos_lookup[2][0]
{ 159, 14 },        // x2 = acos_lookup[4][0]   x1 = acos_lookup[3][0]
  { 133, 14 },        // x2 = acos_lookup[5][0]   x1 = acos_lookup[4][0]
{ 345, 16 },        // x2 = acos_lookup[6][0]   x1 = acos_lookup[5][0]
  { 331, 15 },        // x2 = acos_lookup[7][0]   x1 = acos_lookup[6][0]
{ 1, 6 },        // x2 = acos_lookup[8][0]   x1 = acos_lookup[7][0]
  { 205, 12 },        // x2 = acos_lookup[9][0]   x1 = acos_lookup[8][0]
{ 273, 23 },        // x2 = acos_lookup[10][0]  x1 = acos_lookup[9][0]
  { 920, 23 },        // x2 = acos_lookup[11][0]  x1 = acos_lookup[10][0]
  { 940, 20 },        // x2 = acos_lookup[12][0]  x1 = acos_lookup[11][0]
  { 970, 14 },        // x2 = acos_lookup[13][0]  x1 = acos_lookup[12][0]
  { 990,  8 },        // x2 = acos_lookup[14][0]  x1 = acos_lookup[13][0]
  { 999,  0 }         // x2 = acos_lookup[15][0]  x1 = acos_lookup[14][0]
};



/// Get inverse square root of number using fast inverse square root algorithm
/// made popular by Quake 3.
///
/// @param number Number from which to calculate the inverse square root.
/// @return The inverse square root of input number.

float invSqrt( float number ) ;


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
