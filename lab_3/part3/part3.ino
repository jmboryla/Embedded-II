#include "avr/io.h"

#define BAUD_PRESCALER 0x0067 //U2X0=0 , 0x0067 = 9600 baud

char i = 9;  //loop
int arrayB[10]={0x7,0x3,0x6,0x7,0x3,0x5,0x5,0x7,0x7,0x7};           //array of values to be sent to portB
int arrayD[10]={0xE0,0x0,0xD0,0x90,0x30,0xB0,0xF0,0x0,0xF0,0xB0};   //array of values to be sent to portD

void setup() {
  DDRB=0x0F;  //set output pins for DDRB
  DDRD=0xF4;  //set output pins for DDRD  
  sei();    //enable interrupts
  USART_interrupt_init(); //enables USART interrupts
} 
void loop() 
{
  PORTB = arrayB[i];
  PORTD = arrayD[i];
} 

void USART_interrupt_init(void)
{   
  cli();  //disable interrupts
  UBRR0 = BAUD_PRESCALER;   //sets baud rate to 9600
  UCSR0B = (1<<RXEN0)|(1 << RXCIE0); //RXEN0=1 > receive enable, RXCIE0=1 > complete interrupt enable
  UCSR0C = (0<<USBS0)|(1 << UCSZ01)|(1<<UCSZ00);  //USBS0=0 >1 stop bit, UCSZ01 and UCSZ00 = 1 > 8-bit data
  sei();  //enable interrupts
}

ISR(USART_RX_vect){
  i = UDR0-'0'; //decimal 48 is subtracted from data stored in UDR0 to convert to decimal and stored in i
}


