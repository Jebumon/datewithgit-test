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
int pwm1                = 9;         // the pin that drive MOSFET1
int pwm2                = 10;        // the pin that drive MOSFET2
byte dutycycle1         = 0;         // Duty cycle of MOSFET1
byte dutycycle2         = 0;         // Duty cycle of MOSFET2
int frequency           = 16000;     //frequency (in Hz) for Switching
int lineVoltage         = 0;        //AC Input for Power failure dettection
int acInput             = A0;
int InverterOnSwitch    = 5;         //Inverter on switch
bool Switch             = false;     //Inverter on switch status
bool InverterON         = false;     //Inverter ON/OFF flag
int InverterStatusLED   = 4;         //Status LED
int InverterWarningLED  = 3;         //Warning LED

byte SineWave0_45[40] =     {0, 5, 10, 15, 20, 25, 29, 34, 39, 44,
                            49, 54, 58, 63, 68, 73, 77, 82, 87, 91,
                            96, 100, 105, 109, 113, 118, 122, 126, 131, 135,
                            139, 143, 147, 151, 155, 159, 162, 166, 170, 173};
                           
byte SineWave45_90[40] =   {177, 180, 184, 187, 190, 193, 196, 199, 202, 205,
                            208, 211, 213, 216, 218, 220, 223, 225, 227, 229,
                            231, 233, 235, 236, 238, 239, 241, 242, 243, 244,
                            245, 246, 247, 248, 248, 249, 249, 250, 250, 250};
                           
byte SineWave90_135[40] =  { 250, 250, 250, 250, 249, 249, 248, 248, 247, 246,
                            245, 244, 243, 242, 241, 239, 238, 236, 235, 233,
                            231, 229, 227, 225, 223, 220, 218, 216, 213, 211,
                            208, 205, 202, 199, 196, 193, 190, 187, 184, 180};

byte SineWave135_180[40] =  { 177, 173, 170, 166, 162, 159, 155, 151, 147, 143,
                             139, 135, 131, 126, 122, 118, 113, 109, 105, 100,
                             96, 91, 87, 82, 77, 73, 68, 63, 58, 54,
                             49, 44, 39, 34, 29, 25, 20, 15, 10, 0};
                           

void setup()
{
  pinMode(InverterOnSwitch, INPUT_PULLUP);
  pinMode(acInput, INPUT);
  pinMode(InverterStatusLED, OUTPUT);
  pinMode(InverterWarningLED, OUTPUT);
  
  Serial.begin(9600);
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe(); 

  //sets the frequency for the specified pin
  bool success1 = SetPinFrequencySafe(pwm1, frequency);
  bool success2 = SetPinFrequencySafe(pwm2, frequency);
  
  //if the pin frequency was set successfully, turn status LED on
  if(success1 && success2) 
  {
    pwmWrite(pwm1, dutycycle1); //PWM initialize with Zero dutycycle
    pwmWrite(pwm2, dutycycle2); //PWM initialize with Zero dutycycle
    pinMode(pwm1, OUTPUT);
    pinMode(pwm2, OUTPUT);
    digitalWrite(InverterStatusLED, LOW);   //Status ok Led ON
  }
  else
  {
      digitalWrite(InverterWarningLED, HIGH);   //Warning ok Led ON
  }
}

void loop()
{

    Serial.print("Freq : ");
    Serial.println(frequency);
    Serial.print("Line Voltage :");
    Serial.println(lineVoltage);
    
    lineVoltage = analogRead(acInput);

    Switch = digitalRead(InverterOnSwitch); //Reading On switch

     if(Switch == 0)
     {
      delay(1000);
      Switch = digitalRead(InverterOnSwitch); //Reading On switch
      if(Switch == 0)
      {
      InverterON = !InverterON;              //Toggling INVERTER
      digitalWrite(InverterStatusLED, InverterON);
      }
     }

    if(lineVoltage <= 100 && InverterON == 1)
    {
/////////////////////Inverter PGM////////////////////////   
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

    }
   
}
