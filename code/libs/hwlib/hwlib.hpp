// ==========================================================================
//
// File      : hwlib.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef HWLIB_H
#define HWLIB_H

#ifdef BMPTK_TARGET_arduino_due
   #define HWLIB_INCLUDE_FILE "hwlib-due.hpp"
#endif

#ifdef BMPTK_TARGET_db103
   #define HWLIB_INCLUDE_FILE "hwlib-db103.hpp"
#endif

#ifdef BMPTK_TARGET_arduino_uno
   #define HWLIB_INCLUDE_FILE "hwlib-uno.hpp"
#endif

#ifndef BMPTK_TARGET
   #define HWLIB_INCLUDE_FILE "hwlib-all.hpp"
#endif

#ifndef HWLIB_INCLUDE_FILE
   #error hwlib error: no valid target
#endif

#include HWLIB_INCLUDE_FILE

#endif // HWLIB_ALL_H