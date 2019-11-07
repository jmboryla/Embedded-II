#define BAUD_PRESCALER 0x0067   //U2X0=0 , 0x0067 = 9600 baud

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
   
  USART_send('H');  //sends "Hello World" to serial monitor
  USART_send('e');
  USART_send('l');
  USART_send('l');
  USART_send('o');
  USART_send(' ');
  USART_send('W');
  USART_send('o');
  USART_send('r');
  USART_send('l');
  USART_send('d');
  USART_send('!');
  USART_send('\n');    //sends new line character to serial monitor 
 
}
