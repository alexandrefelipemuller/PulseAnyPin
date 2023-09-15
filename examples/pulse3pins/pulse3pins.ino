#include <pulseAny.h>

void setup()
{
  //Number of ports being used
  initPWM(3);
  
  //Setup each pin (index and pin number)
  pinModePwm(0,2);
  pinModePwm(1,3);
  pinModePwm(2,4);
 
  //frequency of each one in Hz
  setupFreq(0,3);
  setupFreq(1,8);
  setupFreq(2,20);
  
  // Duty goes from 0.1 to 1.9
  analogWrite_(0, 128); // Means 50% of duty
  analogWrite_(1, 64);// Means 25% of duty 
  analogWrite_(2, 192);// Means 75% of duty

}
void loop()
{
  delay(250);
}
