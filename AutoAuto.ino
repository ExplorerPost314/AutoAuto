
// AutoAuto Executive Control Program
// January 2015

// LED Sensor
const int ledPin = 12;

// Obstacle Detection--------------------------
#define DISTANCE_THRESHOLD_CM 40
const int pingTriggerPin = 20;
const int pingPwmPin = 7;
unsigned int Distance = 0;
uint8_t EnPwmCmd[4]={0x44,0x02,0xbb,0x01}; // distance measure command

// Vehicle Control-----------------------------
// Used to control the speed of the left and right wheels
const int leftWheels = 5;
const int rightWheels = 4;
const int leftWheelsEnable = 6;
const int rightWheelEnable = 7;

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
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
  pinMode(leftWheelsEnable, OUTPUT);
  pinMode(rightWheelsEnable, OUTPUT);
  
  // Line Sensors
  pinMode(leftLineSensorPin, INPUT);
  pinMode(middleLineSensorPin, INPUT);
  pinMode(rightLineSensorPin, INPUT);
  
  // Setup distance sensor
  pinMode(pingTriggerPin, OUTPUT); // A low pull on pin COMP/TRIG
  digitalWrite(pingTriggerPin, HIGH); // Set to HIGH
  pinMode(pingPwmPin, INPUT); // Sending Enable PWM mode command
  
  for(int i=0; i<4; i++)
  {
    Serial.write(EnPwmCmd[i]);
  }
  
  // Enable wheel enable/disable pins
  digitalWrite(leftWheelsEnable, HIGH);
  digitalWrite(rightWheelsEnable, HIGH);
}

void loop() 
{     
  // When pressed, start following the line
  if (vehicleStarted)
  {
    // If obstacle is detected, stop vehicle and alert user
    if (IsObstacleInWay())
    {
        //StopVehicle();
        Serial.println("OBSTACLE IN WAY!!");
    }
    else  // If no obstacle, follow line
    {
        int directionToMove = DetermineDirectionToMove();
        if (directionToMove == FORWARD)
        {
            MoveForward();
            //Serial.println("Moving forward");
        }
        else if (directionToMove == LEFT)
        {
            TurnLeft();
            //Serial.println("Moving left");
        }
        else if (directionToMove == RIGHT)
        {
            TurnRight();
            //Serial.println("Moving right");
        }
        else  // If off the line completely, stop vehicle and alert user
        {
            //StopVehicle();    
            //Serial.println("Off line completely!");       
        }
     }
     
     // TODO: Determine the value of the delay
     delay(1000);     
   }       
}

boolean IsObstacleInWay()
{        
    // a low pull on pin COMP/TRIG triggering a sensor reading
    digitalWrite(pingTriggerPin, LOW);
    digitalWrite(pingTriggerPin, HIGH); // reading Pin PWM will output pulses
    unsigned long DistanceMeasured = pulseIn(pingPwmPin,LOW);
    
    if(DistanceMeasured == 50000)
    {   
      Serial.println("Invalid"); // the reading is invalid
    }
    else
    {
      Distance = DistanceMeasured / 50; // every 50us low level stands for 1cm
    }
    //Serial.print("Distance=");
    //Serial.print(Distance);
    //Serial.println("cm");       
           
    if (Distance < DISTANCE_THRESHOLD_CM)
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
   
   Serial.print("Left = ");
   Serial.println(leftLineSensorState);
   Serial.print("Center = ");
   Serial.println(middleLineSensorState);
   Serial.print("Right = ");
   Serial.println(rightLineSensorState);
   
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



