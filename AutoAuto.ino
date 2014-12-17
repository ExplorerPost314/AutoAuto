
// AutoAuto Executive Control Program
// December 2014

// LED Sensor
const int ledPin = 12;

// Obstacle Detection--------------------------
#define DISTANCE_THRESHOLD_INCHES 12
// TODO: Test ultrasonic sensor
const int pingPin = 20;  // reset pin
const int pingPwmPin = 7;
unsigned int duration, inches;
int sensorReadValue = 0;

// Vehicle Control-----------------------------
// Used to control the speed of the left and right wheels
const int leftWheels = 2;
const int rightWheels = 3;

const int MaxSpeedValue = 255;
const int LowSpeedValue = 0; 
const int NormalSpeed = MaxSpeedValue / 2;

// Line Sensors--------------------------------
const int leftLineSensorPin = 41;
const int middleLineSensorPin = 42;
const int rightLineSensorPin = 43;

int leftLineSensorState = 0;
int middleLineSensorState = 0;
int rightLineSensorState = 0;

#define FORWARD 0
#define LEFT 1
#define RIGHT 2
#define ERROR 4

boolean vehicleStarted = true;

void setup() 
{  
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
  // Line Sensors
  pinMode(leftLineSensorPin, INPUT);
  pinMode(middleLineSensorPin, INPUT);
  pinMode(rightLineSensorPin, INPUT);
  
  //pingPin
    //pingPwmPin
    
    pinMode(pingPwmPin, INPUT);
    pinMode(pingPin, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly: 
   
  // When pressed, start following the line
  if (vehicleStarted)
  {
    // If obstacle is detected, stop vehicle and alert user
    if (IsObstacleInWay())
    {
        //StopVehicle();
    }
//    else  // If no obstacle, follow line
//    {
//        int directionToMove = DetermineDirectionToMove();
//        if (directionToMove == FORWARD)
//        {
//            MoveForward();
//        }
//        else if (directionToMove == LEFT)
//        {
//            TurnLeft();
//        }
//        else if (directionToMove == RIGHT)
//        {
//            TurnRight();
//        }
//        else  // If off the line completely, stop vehicle and alert user
//        {
//            StopVehicle();           
//        }
//     }
     
     // TODO: Determine the value of the delay
     delay(200);     
   }

       
}

boolean IsObstacleInWay()
{
  
//    pinMode(pingPin, OUTPUT);          // Set pin to OUTPUT
//    digitalWrite(pingPin, LOW);        // Ensure pin is low
//    delayMicroseconds(2);
//    digitalWrite(pingPin, HIGH);       // Start ranging
//    delayMicroseconds(5);              //   with 5 microsecond burst
//    digitalWrite(pingPin, LOW);        // End ranging
//    pinMode(pingPin, INPUT);           // Set pin to INPUT
//    duration = pulseIn(pingPin, HIGH); // Read echo pulse
//    
//    //TODO: Determine if these values are correct for the ultrasonic sensor
//    inches = duration / 74 / 2;        // Convert to inches based on sensor data
    
    //pingPin
    //pingPwmPin
    
    digitalWrite(pingPin, HIGH);
    
    delayMicroseconds(10);
    
    sensorReadValue = pulseIn(pingPwmPin, HIGH);
           
    digitalWrite(pingPin, LOW);       
    Serial.println(sensorReadValue);            // Display result       
           
    if (inches < DISTANCE_THRESHOLD_INCHES)
    {
       return true;
    }
    else
    {
       return false;
    }
}

int DetermineDirectionToMove()
{
   int returnValue;
  
   leftLineSensorState = digitalRead(leftLineSensorPin);
   middleLineSensorState = digitalRead(middleLineSensorPin);
   rightLineSensorState = digitalRead(rightLineSensorPin);
   
   // If over a black line, value is set to LOW
   //               Left  Middle  Right
   // Go forward -> HIGH LOW HIGH
   // Go left ->    HIGH LOW LOW
   // Go right ->   LOW LOW HIGH
   // Error ->    Any other states
   
   if (leftLineSensorState == HIGH &&
       middleLineSensorState == LOW &&
       rightLineSensorState == HIGH)
   {
      returnValue = FORWARD;
   } 
   else if (leftLineSensorState == HIGH &&
            middleLineSensorState == LOW &&
            rightLineSensorState == LOW)
   {
      returnValue = LEFT;
   }
   else if (leftLineSensorState == LOW &&
            middleLineSensorState == LOW &&
            rightLineSensorState == HIGH)
   {
      returnValue = RIGHT;
   }
   else
   {
      returnValue = ERROR;
   }
   
   return returnValue;
}

void StopVehicle()
{
   vehicleStarted = false;
   analogWrite(rightWheels, LowSpeedValue);
   analogWrite(leftWheels, LowSpeedValue);
   
   digitalWrite(ledPin, HIGH);
}

void MoveForward()
{
    analogWrite(rightWheels, NormalSpeed);
    analogWrite(leftWheels, NormalSpeed);
}

void TurnLeft()
{
    analogWrite(rightWheels, NormalSpeed);
    analogWrite(leftWheels, NormalSpeed/2);
}

void TurnRight()
{
    analogWrite(rightWheels, NormalSpeed/2);
    analogWrite(leftWheels, NormalSpeed);
}



