/*
*  This code is in the public domain.
*  (Do whatever you want with it.)
*/

// Need the Servo library
#include <Servo.h>

// This is our motor.
Servo myMotor;
Servo myMotor2;

// This is the final output
// written to the motor.
String incomingString;


// Set everything up
void setup()
{
  // Put the motor to Arduino pin #9
  myMotor.attach(9);
  myMotor2.attach(7);

  // Required for I/O from Serial monitor
  Serial.begin(9600);
  // Print a startup message
  Serial.println("initializing");
  arm();
}


void loop()
{
  // If there is incoming value
  if(Serial.available() > 0)
  {
    // read the value
    char ch = Serial.read();
    
    if(ch == 'a') {
      arm();
    } else {
  
      /*
      *  If ch isn't a newline
      *  (linefeed) character,
      *  we will add the character
      *  to the incomingString
      */
      if (ch != 13){
        // Print out the value received
        // so that we can see what is
        // happening
        Serial.print("I have received: ");
        Serial.print(ch, DEC);
        Serial.print('\n');
      
        // Add the character to
        // the incomingString
        incomingString += ch;
      }
      // received a newline (linefeed) character
      // this means we are done making a string
      else
      {
        
        if (incomingString == "a") return;
        
        // print the incoming string
        Serial.println("I am printing the entire string");
        Serial.println(incomingString);
      
        // Convert the string to an integer
        int val = incomingString.toInt();
      
        // print the integer
        Serial.println("Printing the value: ");
        Serial.println(val);
      
        /*
        *  We only want to write an integer between
        *  0 and 180 to the motor. 
        */
        if (val > -1 && val < 181)
       {
         // Print confirmation that the
         // value is between 0 and 180
         Serial.println("Value is between 0 and 180");
         // Write to Servo
         myMotor.write(val);
         myMotor2.write(val);
       }
       // The value is not between 0 and 180.
       // We do not want write this value to
       // the motor.
       else
       {
         Serial.println("Value is NOT between 0 and 180");
        
         // IT'S a TRAP!
         Serial.println("Error with the input");
       }
      
        // Reset the value of the incomingString
        incomingString = "";
      }
    }
  }
}

void arm(){
  Serial.print("Arming");
  myMotor.write(0);
  myMotor2.write(0);
  for (int i = 0; i < 5; i++){
    Serial.print(".");
    delay(1000);
  }
  myMotor.write(20);
  myMotor2.write(20);
  Serial.print("   Complete");
}

