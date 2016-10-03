// ==========================================================================
//
// File      : hwlib-matrix-keypad.hpp
// Part of   : hwlib library for V2THDE
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_MATRIX_KEYPAD_H
#define HWLIB_MATRIX_KEYPAD_H

namespace hwlib {
   
/// matrix of switches (keypad) interface
//
/// This class interfaces to a matrix of keys (switches).
class matrix_of_switches {
private:
   port_oc & output;
   port_in & input;

public:

   /// the number of columns
   const int x_size;
   
   /// the number of rows
   const int y_size;

   /// create a matrix interface from the row and column pins
   //
   /// This constructor creates a matrix interface from the
   /// ports that contain the pins that connect to the columns (x direction) 
   /// and the columns (y direction).
   /// The column pins must be an open-collector port,
   /// the row pins muts be an input port that has (internal or external)
   /// pull-up resistors.
   matrix_of_switches( port_oc & output, port_in & input ):
      output( output ), 
      input( input ),
      x_size( output.number_of_pins() ),
      y_size( input.number_of_pins() )
   {}

   /// test whether a particular switch is closed
   //
   /// This function returns whether the switch at column x
   /// and row y is closed.
   /// It doesn't suppress bouncing.
   bool switch_is_closed_at( int x, int y ){
       
      // make (only) the x'th output pin low 
      output.set( ~ ( 0x01 << x ));
      
      // returns whether the y'th input pin is low
      return ( input.get() & ( 0x01 << y )) == 0;
   }
   
};

/// istream from a keaypad matrix
//
/// This class template turns a keypad matrix into an istream
/// (a character input stream).
/// The template parameter is the number of characters in
/// the translation string.
template< int N >
class keypad : public istream {
private:
   matrix_of_switches & matrix;
   char translation[ N ];
   char previous = '\0';
   char buffer = '\0';
   long long int last_timestamp;

public:

   /// create a keypad from a switch matrix and a translation string
   //
   /// The translation string translates a pressed key to a character.
   /// The characters in the string correspond to the keys starting
   /// at the top left (1,1), proceeding colum-first.
   /// Excess characters in the translation string are ignored,
   /// and excess keys are translated to '\0'.
   keypad( 
      matrix_of_switches & matrix,
      const char *translation_string
    ):
      matrix( matrix ),
      last_timestamp( now_us() )
    {
       // fill the translation string, add \0's when the
       // tr parameter is exhausted 
       for( int i = 0; i < N; ++i ){
           if( *translation_string != '\0' ){
               translation[ i ] = *translation_string++;
           } else {
               translation[ i ] = '\0';
           }
       }    
    }  
    
    /// return a press character or '\0' for none
    //
    /// This function returns the character corresponding to 
    /// a switch that is closed, or '\0' when no switch
    /// is closed (or a switch is closed that has no
    /// translation).
    /// This function doesn't suppress bouncing.
    char pressed(){
       for( int x = 0; x < matrix.x_size; ++x ){
          for( int y = 0; y < matrix.x_size; ++y ){
             if( matrix.switch_is_closed_at( x, y )){
                return translation[ x * matrix.y_size + y ];
             }
          }   
       }
       return '\0';
    }
    
    /// return whether a character is available
    //
    /// This function checks whether a next character is available.
    /// When it returns true, an (immediately) folling getc() call
    /// will not block. 
    bool char_available() override {
       if( ( last_timestamp + 50'000 ) > now_us() ){
          return false;
       }
       last_timestamp = now_us();
       
       buffer = pressed();
       if( buffer == '\0' ){
          previous = '\0';
          return false;
       }
       return buffer != previous;
    }
    
    /// return the next available character
    //
    /// This function returns the next available character,
    /// if necessary it will block waiting for it.
    /// Bouncing is suppressed by checking the keypad matrix
    /// at most once every 50 ms.
    char getc() override {
       if( buffer == '\0' ) {
          while( ! char_available() ){
             wait_ms( 1 );
          }
       }
    
       previous = buffer;
       buffer = '\0';
       return previous;
    }
    
};   
   
}; // namespace hwlib

#endif // HWLIB_MATRIX_KEYPAD_H