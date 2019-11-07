int i=9;    //declare i for loop index and initialize to 9
int stopLoop=0; //declare stopLoop, used for stopping loop after first run
int arrayB[10]={0x7,0x3,0x6,0x7,0x3,0x5,0x5,0x7,0x7,0x7};           //array of values to be sent to portB
int arrayD[10]={0xE0,0x0,0xD0,0x90,0x30,0xB0,0xF0,0x0,0xF0,0xB0};   //array of values to be sent to portD

void setup() {
  DDRB=0x0F;    //set DDRB 0000 1111
  DDRD=0xF4;    //set DDRD 1111 0100 
  cli();        //disable interupts
  TCCR1A  = 0;             
  TCCR1B  = 0;            //clear TCCR1A and B
  TCNT1   = 34286;        // preload timer (65536-16MHz/256/2Hz) 
  TCCR1B |= 0b101;    // 1024 prescaler 
  TIMSK1 |= (1<<TOIE1);   // enable timer overflow interrupt 
  sei();
}

void loop() {
  PORTB=arrayB[i];  //out arrayB at index i to portB
  PORTD=arrayD[i];  //out arrayD at index i to portD
}

ISR(TIMER1_OVF_vect)  //ISR triggered by timer 1 overflow
{
  TCNT1 = 34286;  //reset TCNT1
  i--;    //decrement index i
  if (i<0)
  {
    stopLoop=1; //set stopLoop to 1
    i=9;  //reset index i
  }
}
