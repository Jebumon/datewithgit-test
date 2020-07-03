/*

 Mimics the fade example but with an extra parameter for frequency. It should dim but with a flicker 
 because the frequency has been set low enough for the human eye to detect. This flicker is easiest to see when 
 the LED is moving with respect to the eye and when it is between about 20% - 60% brighness. The library 
 allows for a frequency range from 1Hz - 2MHz on 16 bit timers and 31Hz - 2 MHz on 8 bit timers. When 
 SetPinFrequency()/SetPinFrequencySafe() is called, a bool is returned which can be tested to verify the 
 frequency was actually changed.
 
 This example runs on mega and uno.
 */

#include <PWM.h>

//use pin 11 on the Mega instead, otherwise there is a frequency cap at 31 Hz
int pwm1        = 9;         // the pin that drive MOSFET1
int pwm2        = 10;        // the pin that drive MOSFET2
int FreqSwitch1000  = 5;         //Frequency selection Switch
int FreqSwitch100   = 4;         //Frequency selection Switch
byte dutycycle1 = 0;         // Duty cycle of MOSFET1
byte dutycycle2 = 0;         // Duty cycle of MOSFET2
byte fadeAmount = 5;         // how many points to fade the LED by
int frequency   = 16000;      //frequency (in Hz) for Switching
boolean SwitchTemp1000 = HIGH;   //Frequency switch status(low active)
boolean SwitchTemp100  = HIGH;   //Frequency switch status(low active)

int SineWave0_45[40] =     {55,50,40,25,25,10,06,07,07,10,
                           11,11,12,12,13,13,14,14,14,15,
                           16,16,16,17,17,17,18,18,18,19,
                           19,19,19,20,20,20,20,21,21,21};
                           
int SineWave45_90[40] =   {21,22,22,22,22,22,22,22,23,23,
                           23,23,24,24,24,24,24,24,24,24,
                           24,24,25,25,30,30,30,30,30,35,
                           35,35,35,40,40,40,45,45,150,250};
                           
int SineWave90_135[40] =  {255,150,50,45,45,05,05,05,05,10,
                           20,30,35,35,30,30,30,30,25,25,
                           25,24,24,24,24,24,24,24,24,23,
                           23,23,23,23,23,22,22,22,22,21};

int SineWave135_180[40] =  {21,21,21,21,20,20,20,20,19,19,
                           18,17,14,14,14,13,13,13,12,12,
                           10,10,10,10,00,00,00,00,00,00,
                           00,00,00,00,00,00,05,04,00,00};
                           

void setup()
{
  Serial.begin(9600);
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe(); 

  //sets the frequency for the specified pin
  bool success1 = SetPinFrequencySafe(pwm1, frequency);
  bool success2 = SetPinFrequencySafe(pwm2, frequency);
  
  //if the pin frequency was set successfully, turn pin 13 on
  if(success1 && success2) 
  {
    pinMode(13, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(pwm1, OUTPUT);
    pinMode(pwm2, OUTPUT);
    pinMode(FreqSwitch1000, INPUT_PULLUP);
    pinMode(FreqSwitch100,  INPUT_PULLUP);
    digitalWrite(13, HIGH);   //Status ok Led
    //dutycycle1 = dutycycle1 + 50;
    //dutycycle2 = dutycycle2 + 50;
    pwmWrite(pwm1, dutycycle1);
    pwmWrite(pwm2, dutycycle2);
  
  }
}

void loop()
{

    digitalWrite(8, LOW);
    Serial.print("Freq : ");
    Serial.println(frequency);
    
   
/////////////////////////MOSFET1\\\\\\\\\\\\\\\\\\\\\\\\\

     for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm1, SineWave0_45[i]);
     delayMicroseconds(18);
     }

     for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm1, SineWave45_90[i]);
     delayMicroseconds(18);
     }

    for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm1, SineWave90_135[i]);
     delayMicroseconds(18);
     }

     for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm1, SineWave135_180[i]);
     delayMicroseconds(18);
     }
     

//////////////////////////////////////////////////////////

////////////////////////Switch////////////////////////////
    SwitchTemp1000 = digitalRead(FreqSwitch1000);
    if(SwitchTemp1000 == LOW)
    {
    digitalWrite(8, HIGH);
    frequency = frequency + 1000;
    InitTimersSafe(); 
    bool success1 = SetPinFrequencySafe(pwm1, frequency);
    bool success2 = SetPinFrequencySafe(pwm2, frequency);
    SwitchTemp1000 = HIGH;
    }

    SwitchTemp100 = digitalRead(FreqSwitch100);
    if(SwitchTemp100 == LOW)
    {
    digitalWrite(8, HIGH);
    frequency = frequency + 100;
    InitTimersSafe(); 
    bool success1 = SetPinFrequencySafe(pwm1, frequency);
    bool success2 = SetPinFrequencySafe(pwm2, frequency);
    SwitchTemp100 = HIGH;
    }
/////////////////////////////////////////////////////////

/////////////////////////MOSFET2\\\\\\\\\\\\\\\\\\\\\\\\\

for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm2, SineWave0_45[i]);
     delayMicroseconds(18);
     }

     for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm2, SineWave45_90[i]);
     delayMicroseconds(18);
     }

    for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm2, SineWave90_135[i]);
     delayMicroseconds(18);
     }

     for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm2, SineWave135_180[i]);
     delayMicroseconds(18);
     }
//////////////////////////////////////////////////////////
  /*use this functions instead of analogWrite on 'initialized' pins
  digitalWrite(10, HIGH);
  while(brightness >= 0){
  pwmWrite(led, brightness);

  brightness = brightness + fadeAmount;

  if (brightness == 0 || brightness == 255) 
  {
      fadeAmount = -fadeAmount ; 
  }     
  
  delayMicroseconds(105);
  digitalWrite(10, LOW);
  
  }   
  //delay(10); */ 

   
}
