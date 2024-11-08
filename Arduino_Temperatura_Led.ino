#include <Servo.h>

const int pinLED = 13;          // Pin del LED
const int analogIn = A0;        // Pin de entrada analógica (sensor de temperatura)
const int servoPin = 9;         // Pin del servo
int temperatureLimit = 40;      // Límite de temperatura en °C
int rawValue = 0;
double voltage = 0;
double tempC = 0;
double tempF = 0;
Servo servo1;

void setup() {
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
  servo1.attach(servoPin);
}

void loop() {

  if (Serial.available() > 0) {
    char option = Serial.read(); 
    
    if (option == 'a') {        
      digitalWrite(pinLED, HIGH); // Enciende el LED cuando recibe "a"
    }
    else if (option == 'b') {
      digitalWrite(pinLED, LOW);  // Apaga el LED cuando recibe "b"
    }
    else {
     
      temperatureLimit = Serial.parseInt();
      Serial.println("Valor recibido:");
      Serial.println(temperatureLimit);
    }
  }

 
  rawValue = analogRead(analogIn);
  voltage = (rawValue / 1023.0) * 5.0;

  // Convertir el voltaje a temperatura en Celsius
  tempC = (voltage - 0.5) * 100.0; 

  // Convertir la temperatura a Fahrenheit
  tempF = (tempC * 1.8) + 32;

 
  Serial.print("Temperatura en °C: ");
  Serial.println(tempC, 1);
  Serial.print("Temperatura en °F: ");
  Serial.println(tempF, 1);


  if (tempC > temperatureLimit) {
    servo1.write(0);
    delay(1000);
    servo1.write(90);
    delay(1000);
    servo1.write(180);
    delay(1000);
  } else {
    servo1.detach();
  }

  delay(1000); 
}
