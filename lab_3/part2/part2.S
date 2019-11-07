#include "avr/io.h"
#include "part2.h"

              .text
              .global USART_send                   
              .global USART_init
                    

USART_init:
              cli   //disable interrupts
              ldi r21, 0x00   //store 0 for high byte of baud prescaler
              ldi r22, 0x67   //0x67 baud prescaler > 9600 baud
              sts UBRR0L, r22 //baud rate low byte from r22
              sts UBRR0H, r21 //baud rate high byte from r21

              //configure UCSR0B receive and transmit enable
              ldi r18, ((1<<RXEN0)|(1<<TXEN0))  
              sts UCSR0B, r18

              //configure UCSR0C to 1 stop bit, 8 data bits
              ldi r18,((0<<USBS0)|(1 << UCSZ01)|(1<<UCSZ00))
              sts UCSR0C, r18    
              
              sei //enable interrupts             
  

USART_send:
              sts  UDR0, r24
              ret
