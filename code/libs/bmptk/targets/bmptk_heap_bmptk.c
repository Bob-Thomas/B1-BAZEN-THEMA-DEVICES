#include <stdlib.h>

extern unsigned int __heap_start;
extern unsigned int __heap_end;

size_t _first_free = (int) & __heap_start;
size_t _last_free = (int) & __heap_end;

// very simple malloc: advance the _first_free pointer
void * malloc( size_t n ){
   // round up to a multiple of 4 to keep the alignment
   n = ( n + 3 ) & ~ 0x03;
   
   size_t f = _first_free + n;
   if( f > _last_free ){
      return 0;
   } else {
      size_t p = _first_free;
      _first_free = f;
      return (void*) p;
   }
}

// using free must cause a linker error
void free( void * p ){
   void if_you_see_this_you_are_using_free_or_delete();
   if_you_see_this_you_are_using_free_or_delete();
}

size_t bmptk_heap_free(){
   return _last_free - _first_free;   
}   

size_t bmptk_heap_used(){
   return _first_free - ((size_t) &__heap_start);
}   

size_t bmptk_heap_size(){
   return ((size_t) &__heap_end) - ((size_t) &__heap_start);
}   


