/*******************************
 * Motor_Control.ino           *
 * Author: Princeton Robotics: *
 *         Quadcopter Team '15 *
 * Date Created: 2/24/2015     *
 * Description: Controls each  *
 * of the motors from Arduino  *
 * Serial Port.                *
 *******************************/


/* TODO:
 *
 * Right now, the Serial Monitor Controller
 * code only accepts one value and sends that
 * to all the motors. Have the Controller instead
 * accept four values, and send one to each
 * motor (as described below)
 */


/* USAGE:
 *
 * Ensure the motors are connected to OUTPUT ports
 * on the arducopter APM, or PWM pins on another
 * Arduino board. Change the #defines below so
 * the pin number for each connected port is
 * correct.
 *
 * Motor names are based on mount position on
 * the quadcopter: 'f': Front, 'b': Back,
 * 'l': Left, and 'r': Right. So 'flMotor'
 * corresponds to the 'front left motor'.
 *
 * When the code is uploaded, open the Serial
 * Monitor, and ensure that either 'newline' or
 * 'carriage return' is selected in the bottom
 * right corner. You may now enter 4 numbers
 * between 0 and 180 (with 180 as max power)
 * separated by spaces, and those values will
 * be sent to the motors. flMotor will set its
 * power to the first number, frMotor to the
 * second number, blMotor to the third, and
 * brMotor to the fourth.
 *
 * An example line would be:
 * 68 100 0 80
 */


#include <Servo.h>

// Define which pin each motor is attached to
// FL is pin 7
// FR is pin 6
#define FL_MOTOR 2
#define FR_MOTOR 3
#define BL_MOTOR 4
#define BR_MOTOR 5

Servo flMotor;
Servo frMotor;
Servo blMotor;
Servo brMotor;

String incomingString;


void setup()
{
    flMotor.attach(FL_MOTOR);
    frMotor.attach(FR_MOTOR);
    blMotor.attach(BL_MOTOR);
    brMotor.attach(BR_MOTOR);

    Serial.begin(9600);
    Serial.println("Initalizing");
    arm();
}

void loop()
{
    // If the user has inputted something
    if (Serial.available() > 0)
    {
        char ch = Serial.read();

        // If we haven't received a newline or
        // carriage return character, add it to
        // incomingString
        if (ch != 10 && ch != 13) {
            incomingString += ch;
        }

        // If we have received a newline or
        // carriage return character, synthesize
        // the string and send values to motors
        else
        {
            // Input "a" to re-arm the ESCs
            if (incomingString == "a") {
                arm();
            }

            // Send values to motors
            else {
                sendToMotors(incomingString);
            }

            incomingString = "";
        }
    }
}

/* Accepts a string containing four integers  *
 * and sends each of those values to a motor. */
void sendToMotors(String str)
{
    String motorString;
    int motorNum = 0;

    for(int i = 0; i < str.length(); i++)
    {
        char c = str.charAt(i);

        // When we find a space character,
        // parse the string as an int and
        // send it to the proper motor.
        if (c == 32)
        {
            int motorVal = motorString.toInt();

            // Ensure that motorVal is between 0 and 180
            if (motorVal < 0 || motorVal > 180) {
                Serial.println("Please input a value between 0 - 180 for the motors");
            }

            else
            {
                if (motorNum == 0) {
                    flMotor.write(motorVal);
                }
                if (motorNum == 1) {
                    frMotor.write(motorVal);
                }
                if (motorNum == 2) {
                    blMotor.write(motorVal);
                }
                if (motorNum == 3) {
                    brMotor.write(motorVal);
                }
            }

            motorNum++;
            motorString = "";
        }

        // If c is not a space character,
        // append it to motorVal string.
        else {
            motorString += c;
        }
    }
}


/* Arms the ESCs (Readies them for use)    *
 * Arm Sequence: Send a value of 0, wait   *
 * a brief period of time (~5 sec), then   *
 * send a low value (~20). The ESCs should *
 * beep during the arm sequence, but stop  *
 * once it is complete.                    */
void arm()
{
    Serial.print("Arming");

    flMotor.write(0);
    frMotor.write(0);
    blMotor.write(0);
    brMotor.write(0);

    for (int i = 0; i < 5; i++) {
        Serial.print(".");
        delay(1000);
    }

    flMotor.write(20);
    frMotor.write(20);
    blMotor.write(20);
    brMotor.write(20);

    Serial.println("    Complete!");
}
