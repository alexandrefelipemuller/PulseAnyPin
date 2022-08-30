#include <Arduino.h>
int *out_freq;
unsigned long *previousMillis; 
int *pulse_pin; // Define pinos para pulsar
float *duty;
int pins;

// Config pin to be used
void pinModePwm(int num, int pin){
  pinMode(pin,OUTPUT);
  pulse_pin[num]=pin;
}

// Output a value (num is not pin number, is the number provided on pinModePwm)
void analogWrite_(int num, int value){
  // This code can be used on production, commented just o be visible
  //out_freq[num] = 100;  
  
  // Duty goes from 0.01 to 1.99
  duty[num] = value/128.0f;
}


ISR(TIMER1_OVF_vect)
{
 unsigned long currentMillis = millis();
 unsigned long elapsedTime, pulseTime;
  for (int i=0;i < pins; i++){
    if (out_freq[i] == 0.0)
      digitalWrite(pulse_pin[i],LOW);
    else
    {
      elapsedTime = currentMillis - previousMillis[i];
      if (digitalRead(pulse_pin[i]) == HIGH)
            pulseTime = (1000.0/(out_freq[i]*2))*duty[i];
      else
            pulseTime = (1000.0/(out_freq[i]*2))/duty[i];
      if (elapsedTime >= pulseTime) {
          previousMillis[i] = currentMillis;
          digitalWrite(pulse_pin[i],!digitalRead(pulse_pin[i]));
      }
    }
  }
  TCNT1 = 65530; //configura timer
}

void setupTimer1(){
    // Configuração do timer1 
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1
 
  TCNT1 = 65530; //configura timer
  
  TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1
}

void initPWM(int num){
  pins = num;
  setupTimer1();
  // set up pulse pins
  out_freq = (int*) malloc(sizeof(int)*pins);
  previousMillis = (unsigned long*) malloc(sizeof(unsigned long)*pins); 
  pulse_pin = (int*) malloc(sizeof(int)*pins); // Define pinos para pulsar
  duty = (float*) malloc(sizeof(float)*pins);
  for (int i=0; i<pins; i++){
    out_freq[i]=100;
    previousMillis[i]=0;
    pulse_pin[i]=-1;
    duty[i]=1;
  }
}

void setupFreq(int pinNum, int freq){
 out_freq[pinNum] = freq;
}
