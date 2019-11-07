#include "avr/io.h"
#define BAUD_PRESCALER 0x0067   //U2X0=0 , 0x0067 = 9600 baud

const char arrayA[13]={'H','e','l','l','o',' ','W','o','r','l','d','!','\n'};
int i=0; //index variable

void USART_init()
{
  
  UBRR0 = BAUD_PRESCALER; //sets baud rate to 9600 
  UCSR0C = ((0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00));  //USBS0 = 0 > 1 stop bit, UCSZ00 = 1 and UCSZ01 = 1 > 8 data bits
  UCSR0B=((1<<RXEN0)|(1<<TXEN0));   //Receive and transmit enabled
}

void USART_send(char i){
 
 
  while(!(UCSR0A&(1<<UDRE0)));    //checks status register, waits until UDR0 is ready for new data 
    UDR0 = i;  //sends new data to UDR0
}


void setup() 
{

  USART_init();
  cli();                        //disable interupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 46875;                //16MHz/(1024 * .33Hz)
  TCCR1B |= (1<<WGM12);         // CTC Mode (clear timer on compare)     
  TCCR1B |= 5;                  // 1024 counter prescaler  
  TIMSK1 |= (1<<OCIE1A);        // Compare interrupt 
  sei();                        //Enable interupts
}

void loop(){

}

ISR(TIMER1_COMPA_vect)
{
    for (i=0; i<13; i++){
    USART_send(arrayA[i]);
  }
   
}
