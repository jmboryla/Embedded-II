//DDRB = A-C
//DDRD = D-F
int i=9;    //declare i for loop index and initialize to 9
int arrayB[10]={0x7,0x3,0x6,0x7,0x3,0x5,0x5,0x7,0x7,0x7};           //array of values to be sent to portB
int arrayD[10]={0xE0,0x0,0xD0,0x90,0x30,0xB0,0xF0,0x0,0xF0,0xB0};   //array of values to be sent to portD


void setup() {
  DDRB=0x0F;  //set output pins for DDRB
  DDRD=0xF4;  //set output pins for DDRD  
  cli();    //disable interupts
  EIMSK |= (1<<INT0);     //enable int0
  EICRA |= (1<<ISC01);    //trigger interupt on falling edge
  sei();    //enable interupts
}

void loop() {
  PORTB=arrayB[i];  //out arrayB at index i to portB
  PORTD=arrayD[i];  //out arrayD at index i to portD
}

ISR(INT0_vect)  //ISR is triggered by int0 on falling edge
{
  i--;  //decrement index
  if (i<0)  //if index is negative, reset to 9
  {
    i=9;
  } 
}
