#include "avr/io.h"
#include "part2.h"

char i = 9;  //loop
int arrayB[10]={0x7,0x3,0x6,0x7,0x3,0x5,0x5,0x7,0x7,0x7};           //array of values to be sent to portB
int arrayD[10]={0xE0,0x0,0xD0,0x90,0x30,0xB0,0xF0,0x0,0xF0,0xB0};   //array of values to be sent to portD

void setup() 
{
  DDRB=0x0F;  //set output pins for DDRB
  DDRD=0xF4;  //set output pins for DDRD  

  USART_init();
  cli();                        //disable interupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15625;                //16MHz/(1024 * 1Hz)
  TCCR1B |= (1<<WGM12);         // CTC Mode (clear timer on compare)     
  TCCR1B |= 5;                  // 1024 counter prescaler  
  TIMSK1 |= (1<<OCIE1A);        // Compare interrupt 
  sei();                        //Enable interupts
}

void loop() 
{
   PORTB=arrayB[i];  //out arrayB at index i to portB to display segments A-C on seven segment
   PORTD=arrayD[i];  //out arrayD at index i to portD to display segments D-G on seven segment
}


ISR(TIMER1_COMPA_vect)
{
  i --;    //decrements i
  if (i < 0)
   i = 9;            //resets index to 9
   
  USART_send(i+'0');  //sends decimal value of i to serial monitor
  USART_send('\n');    //sends new line character to serial monitor 
 
}
