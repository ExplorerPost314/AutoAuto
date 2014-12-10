// Tests the ultrasonic sensor by printing messages to the terminal
// if an obstacle is detected.

const int pingPin = 11;
unsigned int duration, inches;

void setup() {
  Serial.begin(9600);
}

void loop() {
  obst();
}

// Returns true if obstacle detected, false otherwise.
boolean obst()
{
  // Code to send pings out of the sensor and listen to the result
  pinMode(pingPin, OUTPUT);          // Set pin to OUTPUT
  digitalWrite(pingPin, LOW);        // Ensure pin is low
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);       // Start ranging
  delayMicroseconds(5);              //   with 5 microsecond burst
  digitalWrite(pingPin, LOW);        // End ranging
  pinMode(pingPin, INPUT);           // Set pin to INPUT
  duration = pulseIn(pingPin, HIGH); // Read echo pulse
  inches = duration / 74 / 2;        // Convert to inches
  
  Serial.println(inches);            // Display result
  
  // Delay between obstacle detection checks
  delay(200);	
 
  if(inches < 12)
  {
      Serial.println("obst alert");
      return true;
  }
  else
  {
      Serial.println("no obst");
      return false;
  }
}
