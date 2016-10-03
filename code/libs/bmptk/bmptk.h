//***************************************************************************
//
// file : bmptk/bmptk.h
//
// Copyright (c) 2012 ... 2015 Wouter van Ooijen (wouter@voti.nl)
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// This is the one header file a user should include to use bmptk.
//
//***************************************************************************

#ifndef _BMPTK_H_
#define _BMPTK_H_

#include <stdlib.h>

// ==========================================================================
// 
// BMPTK_HERE debug macro
//
// ==========================================================================

//! file-name : line-number macro
//
//! The macro BMPTK_HERE tranlsates to a newline, the file-name, ":",
//! and the line-number of the place where the BMPTK_HERE macro
//! appears. This can be usefull for debug logging.
#define BMPTK_STRINGYFY(X) #X
#define BMPTK_HERE2(F, L) ( "\n" F ":" BMPTK_STRINGYFY( L ) " " )
#define BMPTK_HERE BMPTK_HERE2( __FILE__, __LINE__ )


// ==========================================================================
// 
// include the target-specific header file(s)
//
// These macros are supplied by the makefile:
// BMPTK_INCLUDE_CHIP  : the chip (register) definition files
// BMPTK_INCLUDE_BMPTK : the bmptk functional implementation (as yet empty)
//
// ==========================================================================

#define BMPTK_QUOTE(X) BMPTK_STRINGYFY( X )

#ifdef BMPTK_INCLUDE_CHIP
#include BMPTK_QUOTE( BMPTK_INCLUDE_CHIP )
#endif
#ifdef BMPTK_INCLUDE_BMPTK
#include BMPTK_QUOTE( BMPTK_INCLUDE_BMPTK )
#endif

#ifdef __cplusplus
extern "C" {
#endif

size_t bmptk_heap_size();
size_t bmptk_heap_free();
size_t bmptk_heap_used();

size_t bmptk_stack_size();
size_t bmptk_stack_free();
size_t bmptk_stack_used();

#ifdef __cplusplus
}
#endif


#endif // #ifndef _BMPTK_H_