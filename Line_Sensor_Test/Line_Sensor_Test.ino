// This program is used to test the line sensor and see if it works.

const int led = 13;
const int lineSensor = 8;
int lineSensorState = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  pinMode(lineSensor, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  
  lineSensorState = digitalRead(lineSensor);
  
  if (lineSensorState == LOW) // If black surface detected, turn on light
  {
      digitalWrite(led, HIGH);
  }
  else
  {
      digitalWrite(led, LOW);
  }
  
}
