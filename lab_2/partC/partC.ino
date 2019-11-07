int i=9;    //declare i for loop index and initialize to 9
int arrayB[10]={0x7,0x3,0x6,0x7,0x3,0x5,0x5,0x7,0x7,0x7};           //array of values to be sent to portB
int arrayD[10]={0xE0,0x0,0xD0,0x90,0x30,0xB0,0xF0,0x0,0xF0,0xB0};   //array of values to be sent to portD

void setup() {
  DDRB=0x0F;    //set DDRB 0000 1111
  DDRD=0xF4;    //set DDRD 1111 0100 
  cli();    //disable interupts
  PCICR |= (1<<PCIE2);
  PCMSK2 |= (1<<PCINT18);
  sei();  //enable interupts
}

void loop() { 
  PORTB=arrayB[i];  //out arrayB at index i to portB
  PORTD=arrayD[i];  //out arrayD at index i to portD
}

ISR(PCINT2_vect)  //ISR is triggered by pin 2 rising and falling edge
{
  i--;  //decrement index
  if (i<0)  //if index is negative, reset to 9
    i=9;
}
