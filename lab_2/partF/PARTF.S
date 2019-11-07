#include "avr/io.h"                                             
              
  .global  setup                  
  .global  loop                    
  .global  TIMER1_OVF_vect

setup:
      ldi r24, 9  
      ldi r16, 0xF4  
      out 10, r16       //set DDRD           
      ldi r16, 0x0F 
      out 4, r16        //set DDRB                
      cli               //clear interupts
      ldi r16, 0    
      sts TCCR1A, r16
      sts TCCR1B, r16   //Clear TCCR1A and TCCR1B
      ldi r26, 0xEE 
      ldi r27, 0x85     //0x85EE(34286)=65536-((16MHz/1024)/.5Hz)        
      sts TCNT1L, r26
      sts TCNT1H, r27   //TCNT1= 0x85EE (34286)
      ldi r18, 0x5    
      sts TCCR1B, r18   //1024 prescaler             
      ldi r18, 0x1
      sts TIMSK1, r18   //enable timer overflow interupt         
      sei               //enable interupts          
      ret
loop:
      cpi r24,9   //call digit function using loop comparison register r24
      breq DIG9  
      cpi r24,8
      breq DIG8
      cpi r24,7
      breq DIG7
      cpi r24,6
      breq  DIG6
      cpi r24,5
      breq  DIG5 
      cpi r24,4
      breq  DIG4
      cpi r24,3
      breq  DIG3
      cpi r24,2
      breq  DIG2
      cpi r24,1
      breq  DIG1
      cpi r24,0
      breq  DIG0
      brlo  setDig  //if loop counter is negative it gets reset to 9
DIG9:   
      ldi r16, 0xB0  //r16 goes to portD, r17 goes to portB
      ldi r17, 0x7  
      out 0x0B, r16 
      out 0x5, r17 
      ret  

DIG8:  
      ldi r16, 0xF0  
      ldi r17, 0x7  
      out 0x0B, r16 
      out 0x5, r17 
      ret
      
DIG7:  
      ldi r16, 0x0  
      ldi r17, 0x7  
      out 0x0B, r16 
      out 0x5, r17 
      ret
      
DIG6:  
      ldi r16, 0xF0  
      ldi r17, 0x5  
      out 0x0B, r16 
      out 0x5, r17 
      ret

DIG5:  
      ldi r16, 0xB0  
      ldi r17, 0x5  
      out 0x0B, r16 
      out 0x5, r17 
      ret
      
DIG4:  
      ldi r16, 0x30  
      ldi r17, 0x3  
      out 0x0B, r16 
      out 0x5, r17 
      ret
      
DIG3:  
      ldi r16, 0x90  
      ldi r17, 0x7  
      out 0x0B, r16 
      out 0x5, r17 
      ret

DIG2:  
      ldi r16, 0xD0  
      ldi r17, 0x6  
      out 0x0B, r16 
      out 0x5, r17 
      ret
      
DIG1:  
      ldi r16, 0x0  
      ldi r17, 0x3  
      out 0x0B,r16 
      out 0x5, r17 
      ret 

DIG0:   
      ldi r16, 0xE0 
      ldi r17, 0x7  
      out 0x0B, r16    
      out 0x5, r17      
      ret
     
setDig:
      ldi   r24,9 //reset loop counter
      ret

TIMER1_OVF_vect:  //timer overflow function is called when timer overflows
      ldi r26, 0xEE 
      ldi r27, 0x85               
      sts TCNT1L, r26
      sts TCNT1H, r27 //reset TCNT1             
      dec r24 //decrement loop counter
      reti  //return from interupt
