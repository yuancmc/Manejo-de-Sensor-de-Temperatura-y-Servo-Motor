#include <Servo.h>

const int analogIn = a0;
const int servoPin = 9;
int temperatureLimit = 15; 

int RawValue = 0; 
double Voltage = 0;
double temC = 0;
double temF = 0;
Servo Servo1;

void setup(){
  Serial.begin(9600);
  Servo1.attach(ServoPin);
}
void loop(){
  if(serial.available()>0){
    
    temperaturaLimit = Serial.parseInt();
    serial.printIn("Valor recibido");
    Serial.print(temperauraLimit);
    RawValue = analogRead(analogIn);
    voltage = (RawValue / 1023.0)*5000; 
    temC = Voltage*0.1; 
    temF = (temC*1.8)+32; 
    serial.printIn(tempC, 1);
    
    if(temC > temperatureLimt){
      
      servo1.write(0);
      delay(1000);
      
      servo1.write(90);
      delay(1000);
      
      servo1.write(180);
      delay(1000);
    } else {
      servo1.detach();
    }
  }
}
