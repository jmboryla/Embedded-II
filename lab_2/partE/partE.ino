int i=9;  //variable i for index
int arrayB[10]={0x7,0x3,0x6,0x7,0x3,0x5,0x5,0x7,0x7,0x7}; //array of values to out PORTB
int arrayD[10]={0xE0,0x0,0xD0,0x90,0x30,0xB0,0xF0,0x0,0xF0,0xB0}; //array of values to out PORTD

void setup() {
  DDRB=0x0F;  //set DDRB 0000 1111
  DDRD=0xF4;  //set DDRD 1111 0100
  cli();    //disable interupts
  TCCR1A  = 0;   
  TCCR1B  = 0;   //clear TCCR1A and B
  OCR1A   = 31250;         
  TCCR1B |= 0xD;    // 1024 prescaler CTC Mode 
  TIMSK1 |= (1<<OCIE1A);   // enable timer overflow interrupt 
  sei();
}

void loop() {
  PORTB=arrayB[i];  //send arrayB at i out PORTB
  PORTD=arrayD[i];  //send arrayD at i out PORTD
}

ISR(TIMER1_COMPA_vect)  //ISR is triggered when timer reaches OCR1A value and is cleared (CTC mode)
{
  i--;  //decrement index
  if (i<0)  //if index is negative reset to 9
  i=9;
}
