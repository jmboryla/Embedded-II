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
  TCNT1   = 49911;        // preload timer (65536-(16MHz/1024)/1Hz) 
  TCCR1B |= 0b101;        // 1024 prescaler 
  TIMSK1 |= (1<<TOIE1);   // enable timer overflow interrupt 
  EIMSK |= (1<<INT0);     //enable int0
  EICRA |= (1<<ISC01);    //trigger int0 on falling edge
  sei();      //enable interupts
}

void loop() {
  if(stopLoop)  //stops timer from looping after first loop
  i=9;
  PORTB=arrayB[i];  //out arrayB at index i to portB
  PORTD=arrayD[i];  //out arrayD at index i to portD
}

ISR(INT0_vect){
  stopLoop=0; //resets stopLoop value to zero with int0
}

ISR(TIMER1_OVF_vect)
{
  TCNT1 = 49911;  //reset timer value
  i--;    //decrement index i
  if (i<0)
  {
    stopLoop=1; //set stopLoop to 1
    i=9;  //reset index i
  }
}
