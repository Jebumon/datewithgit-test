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
int frequency   = 1500;      //frequency (in Hz) for Switching
boolean SwitchTemp1000 = HIGH;   //Frequency switch status(low active)
boolean SwitchTemp100  = HIGH;   //Frequency switch status(low active)

byte SineWave0_45[40] =     {0, 4, 8, 12, 16, 20, 24, 27, 31, 35,
                             39, 43, 47, 50, 54, 58, 58, 58, 58, 58, 
                             58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 
                             58, 58, 58, 58, 58, 58, 58, 58, 58, 58,};
                           
byte SineWave45_90[40] =   {58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 
                            58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 
                            100, 100, 100, 100, 100, 100, 100, 194, 194, 195, 
                            196, 197, 198, 198, 249, 250, 250, 250, 250, 250};
                           
byte SineWave90_135[40] =  {250, 250, 250, 250, 250, 249, 198, 198, 198, 197, 
                            100, 100, 100, 100, 100, 100, 100, 189, 188, 186, 
                            58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 
                            58, 58, 58, 58, 58, 58, 58, 58, 58, 58};

byte SineWave135_180[40] =  {58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 
                             58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 
                             58, 58, 58, 58, 58, 58, 54, 50, 47, 43, 
                             39, 35, 31, 27, 24, 20, 16, 12, 8, 0};
                           

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
