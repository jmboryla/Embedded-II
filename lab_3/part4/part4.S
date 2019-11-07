#include "avr/io.h"
          .data

          .text
          .global setup                  
          .global loop                    
          .global USART_RX_vect
             
setup:        
          ldi r24, 9  //initialize r24 to 9
          
          //set DDRD
          ldi r16, 0xF4  
          out 10, r16                
          
          //set DDRB
          ldi r16, 0x0F 
          out 4, r16           
          
          cli   //disable interrupts

          //set baud rate to 9600
          ldi r21, 0x00 
          ldi r22, 0x67
          sts UBRR0L, r22
          sts UBRR0H, r21
          
          //set UCSR0B to receive enable, and receive interrupt enable
          ldi r18, ((1 << RXEN0)|(1 << RXCIE0))
          sts UCSR0B, r18

          //set UCSR0C to 1 stop bit, 8 data bits
          ldi r18,((0<<USBS0)|(1 << UCSZ01)|(1<<UCSZ00))
          sts UCSR0C, r18
          
          sei //enable interrupts             
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
          rjmp defaul
                       
defaul:             
          ret
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
     
USART_RX_vect:  
          lds  r24, UDR0  //load number received in UDR0 to r24
          subi r24, 48    //subtract 48 to convert from ASCII to decimal
          reti
