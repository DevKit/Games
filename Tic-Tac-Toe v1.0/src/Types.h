//////////////////////////////////////////////////////////////////
// Author: DevCNub
// Name: types.h
// Date: 22.06.2013
// Purpose: Transferable types for porting applications on diff.
//          platforms and devices.
//
// Notes: The ANSI C standard doesn't define the size of the types in
//        bits or bytes. The types are defined in terms of
//        the minimum range each type must hold.
//////////////////////////////////////////////////////////////////


#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED


typedef signed   char  Sint8;     // Range: -128 to 127,      Min. size in bits: 8
typedef unsigned char  Uint8;     // Range: 0 to 255,         Min. size in bits: 8
typedef signed   short Sint16;    // Range: -32768 to 32767   Min. size in bits: 16
typedef unsigned short Uint16;    // Range: 0 to 65535,       Min. size in bits: 16
typedef signed   int   Sint32;    // Range: -32768 to 32767,  Min. size in bits: 16
typedef unsigned int   Uint32;    // Range: 0 to 65535,       Min. size in bits: 16
typedef signed   long  Slong32;   // Range: +-(2^31 - 1),     Min. size in bits: 32
typedef unsigned long  Ulong32;   // Range: 0 to (2^32 - 1),  Min. size in bits: 32
typedef float          F32;       // Range: 6 digits preci.,  Min. size in bits: 32
typedef double         D64;       // Range: 10 digits preci., Min. size in bits: 64


typedef Sint8 Schar;
typedef Uint8 Uchar;


#endif // TYPES_H_INCLUDED
