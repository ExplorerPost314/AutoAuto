


int M1_L = 5;    // Left side motor pin
int M1_R = 4;    //Right side motor pin
int E1_L = 6;    //Left side enable pin
int E1_R = 7;    //Right side enable pin

void setup()
{
pinMode (M1_L, OUTPUT);
pinMode (M1_R, OUTPUT);

}
  


void loop()  { 
digitalWrite (M1_L, HIGH);
digitalWrite (M1_R, HIGH);
analogWrite (E1_R, 100);
analogWrite (E1_L, 100);

  
  
}


