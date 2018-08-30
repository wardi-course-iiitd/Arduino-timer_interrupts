////////////////////////////////////////////////////////////
/* Code written by Gaurav Duggal 27-08-2018               */
//Reference: Atmega 328 datasheet and Arduino Reference page
////////////////////////////////////////////////////////////

#define positive 3
#define negative 2
#define sig A0
volatile unsigned int v = 0;
volatile byte flag = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(positive,OUTPUT);
pinMode(negative,INPUT);
digitalWrite(positive, HIGH);
digitalWrite(negative, LOW);
pinMode(13,OUTPUT);
cli();
timer_init();
sei();
}

void loop() 
{
  if (flag==1)
  {
  	Serial.print("$");
    Serial.println(v);
    flag = 0;
    
  }
}

void timer_init()
{
  
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 62.5hz increments
  // = (16*10^6) / (OCR2A*1024) - 1 is the frequency the ISR is called
  //set for 62.5 Hz
  OCR2A = 249;
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 1024 prescaler
  TCCR2B |= (1 << CS22) | (1 << CS21)| (1 << CS20)  ;   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
}


ISR(TIMER2_COMPA_vect){
//to check for buffer overruns
if (flag==1)
  digitalWrite(13,HIGH);
else
  digitalWrite(13,LOW);
  
flag = 1;
v = analogRead(A0);
}
