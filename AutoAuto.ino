//General autoAuto Project Code
const int button = 2;
const int led = 13;
boolean vechicleState=false;

enum lineStatus    //using enumeration to feed the movement function a direction
{
   forward,
   left,
   right
};

void setup() 
{
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
}

void loop()
{
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) 
    {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH); 
     vehicalState=true;
     
    } 
  else 
    {
    // turn LED off:
    digitalWrite(ledPin, LOW); //unneeded? LED already off
    }
   while(vehicalState==true)
    {
      if (obstacleDetected()==false)
      {
       //function that detects direction to move goes here
        
       //function that moves vehicle in specified direction
       lineStatus lineDirection = lineFollower();
       if(lineDirection==forward)
          {
              //move Forward
          }       
       if (lineDirection==left)
         {
           //Left Wheels High 
         }
       if(lineDirection==right)
         {
            //Right Wheels High
         }
       }
    }
}

lineStatus lineFollower()
{
  //if(leftLineBool==false && rightLineBool==false)
          //return forward;
  //if( leftLineBool==false && rightLineBool==true)
          // return right;
  //if(leftLineBool==true && rightLineBool==false)
          // return left;
}

/*void killEngine()
   {
     vehicalState=false;
     //Stops power to the vehicle , and ends the loops
    // Blinks LED/ LCD screen
   }*/
