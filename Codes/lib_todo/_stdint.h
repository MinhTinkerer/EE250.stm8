/**
    \file _stdint.h.h
    \brief Definie des types standards
    \author SCHLOTTERBECK Guillaume
    \version 1.0
    \date 10/06/2013
**/


#ifndef _STDINT_H
#define _STDINT_H



/* 7.18.1.1  Exact-width integer types */
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed long int32_t;
typedef unsigned long uint32_t;



/* 7.18.2.1  Limits of exact-width integer types */
#define INT8_MIN (-128) 
#define INT16_MIN (-32768)
#define INT32_MIN (-2147483647 - 1)

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647

#define UINT8_MAX 0xff /* 255U */
#define UINT16_MAX 0xffff /* 65535U */
#define UINT32_MAX 0xffffffff  /* 4294967295U */


#endif

