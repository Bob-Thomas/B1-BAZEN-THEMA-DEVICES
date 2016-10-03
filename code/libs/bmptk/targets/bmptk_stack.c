// This file supplies the BMPTK stack space variable.
//
// The size is specified by the STACK_SIZE command line argument,
// which can be NATIVE, AUMTOMATIC, or a positive integer value.

// NATIVE means do not create a stack, the native stack is used.
// supply a dummy size to make the compilation successful.
#define NATIVE 8

// AUTOMATIC means calculate the required stack size and allocate a stack 
// of that size, but the application must first be linked, and for that 
// a dummy stack must be used to make the compilation successful.
#define AUTOMATIC 8

#include <stdlib.h>

unsigned char bmptk_stack[ STACK_SIZE ] 
   __attribute__ (( section( ".bmptk_stack" )));
   
unsigned char bmptk_stack_beyond
    __attribute__ (( section( ".bmptk_stack" )));
   
size_t bmptk_stack_size(){
   return STACK_SIZE;   
}   

size_t bmptk_stack_free(){
   for( size_t n = 0; n < STACK_SIZE; ++n ){
      if( bmptk_stack[ n ] != 0x00 ){
         return n;
      }
   }
   return STACK_SIZE;
}

size_t bmptk_stack_used(){
   return STACK_SIZE - bmptk_stack_free();   
}   