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
int frequency   = 1000;      //frequency (in Hz) for Switching
boolean SwitchTemp1000 = HIGH;   //Frequency switch status(low active)
boolean SwitchTemp100  = HIGH;   //Frequency switch status(low active)

int SineWave0_45[40] =     {128,133,138,142,147,152,157,162,167,172,
                            176,181,185,190,194,198,202,206,210,214,
                            218,221,224,228,231,234,236,239,241,243,
                            245,247,249,250,251,253,253,254,255,255};
                           
int SineWave45_90[40] =   {255,255,255,254,253,253,251,250,249,247,
                            245,243,241,239,236,234,231,228,224,221,
                            218,214,210,206,202,198,194,190,185,181,
                            176,172,167,162,157,152,147,142,138,133};
                           
int SineWave90_135[40] =  {128,122,117,113,108,103,98,93,88,83,
                           79,74,70,65,61,57,53,49,45,41,
                           37,34,31,27,24,21,19,16,14,12,
                           10,8,6,5,4,2,2,1,0,0};

int SineWave135_180[40] =  {0,0,0,1,2,2,4,5,6,8,
                            10,12,14,16,19,21,24,27,31,34,
                            37,41,45,49,53,57,61,65,70,74,
                            79,83,88,93,98,103,108,113,117,122};
                           

void setup()
{
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
   
/////////////////////////MOSFET1\\\\\\\\\\\\\\\\\\\\\\\\\

     for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm1, SineWave0_45[i]);
     }

     for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm1, SineWave45_90[i]);
     }

    for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm1, SineWave90_135[i]);
     }

     for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm1, SineWave135_180[i]);
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
     }

     for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm2, SineWave45_90[i]);
     }

    for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm2, SineWave90_135[i]);
     }

     for(int i=0; i <=39; i++)
    {
     pwmWrite(pwm2, SineWave135_180[i]);
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
