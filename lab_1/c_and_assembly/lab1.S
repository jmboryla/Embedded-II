#include "lab1.h"

.data

     .global setup 
     .global loop 
     .global nine
     .global eight
     .global seven
     .global six
     .global five
     .global four
     .global three
     .global two
     .global one
     .global zero
     .global reset
     .global Delay_1sec

.text 

setup: ldi r24,0xFC //load 1111 1100 to r24 to set DDRD
      clr r25
      out 0xA,r24 //set DDRD pins 2-7 to output 
      sbi 4,0   //set DDRB pin 0 to output
      ret  
      
   
  
zero:   //outputs value of r26 to port D  and r27 to port b
      ldi r26, 0xFC 
      ldi r27, 0x0  
      out 0x0B, r26 
      out 5, r27 
      ret

one:  
      ldi r26, 0x18  
      ldi r27, 0x0  
      out 0x0B, r26 
      out 5, r27 
      ret 

two:  
      ldi r26, 0x6C  
      ldi r27, 0x1  
      out 0x0B, r26 
      out 5, r27 
      ret 


three:  
      ldi r26, 0x3C  
      ldi r27, 0x1  
      out 0x0B, r26 
      out 5, r27 
      ret

four:  
      ldi r26, 0x98  
      ldi r27, 0x1  
      out 0x0B, r26 
      out 5, r27 
      ret

five:  
      ldi r26, 0xB4  
      ldi r27, 0x1  
      out 0x0B, r26 
      out 5, r27 
      ret

six:  
      ldi r26, 0xF4  
      ldi r27, 0x1  
      out 0x0B, r26 
      out 5, r27 
      ret


seven:  
      ldi r26, 0x1C  
      ldi r27, 0x0  
      out 0x0B, r26 
      out 5, r27 
      ret


eight:  
      ldi r26, 0xFC  
      ldi r27, 0x1  
      out 0x0B, r26 
      out 5, r27 
      ret

nine:  
      ldi r26, 0x9C  
      ldi r27, 0x1  
      out 0x0B, r26 
      out 5, r27 
      ret


//put delays in a loop 

Delay_1sec:  

      ldi r16, 128 

Delay1: 

      ldi r17, 125 

Delay2: 

      ldi r18, 250 

Delay3: 

      dec r18 
      nop 
      brne Delay3 

      dec r17 
      brne Delay2 

      dec r16 
      brne Delay1 
      ret

reset: //turns off all LEDS
      out 0xB,r25
      cbi 5,0
      ret
