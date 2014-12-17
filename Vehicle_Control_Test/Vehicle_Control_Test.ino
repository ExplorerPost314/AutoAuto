// Used to control the speed of the left and right wheels
const int leftWheels = A6;
const int rightWheels = A7;

// Used to enable/disable the left and right wheels
const int leftEnable = 14;
const int rightEnable = 15;

const int MaxSpeedValue = 255;
const int LowSpeedValue = 0; 

void setup() 
{
  // put your setup code here, to run once:
  pinMode(leftEnable, OUTPUT); 
  digitalWrite (leftEnable, LOW);
  
  pinMode(rightEnable, OUTPUT); 
  digitalWrite (rightEnable, LOW);
  
  // NOTE: Values of 127 or lower do not seem to power the wheels
  analogWrite(rightWheels, MaxSpeedValue);
  analogWrite(leftWheels, MaxSpeedValue);
}

void loop() 
{

}
