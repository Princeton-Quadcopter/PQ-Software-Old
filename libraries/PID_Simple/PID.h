/* PID.h
 * Author: Lance Goodridge
 * Description: A general PID Controller.
 */

#pragma once

class PID
{
public:
    PID(int interval, double pGain, double iGain, double dGain);   // Constructor
    void update(double newValue, double newTarget);   // Update data and errors
    void resetErrors();    // Reset each variable + start taking fresh data
    double getOutput();    // Returns the controller output value
    
private:
    int interval;    // The sampling interval, in milliseconds
    double pGain;    // Adjusts how much pError affects the output
    double iGain;    // Adjusts how much iError affects the output
    double dGain;    // Adjusts how much dError affects the output
    double value;    // The measured value of the output
    double previousValue;    // The previous value of the output
    double target;   // The desired value of the output
    double pError;   // Proportional Error: Measures our current error
    double iError;   // Integral Error: Evaluates and adjusts for past errors
    double dError;   // Derivative Error: Predicts and adjusts for future error
    double previousErrors[4];     // Keeps track of the last four errors
    void updatePreviousErrors();  // Updates the previousErrors array
    void calculatePError();       // Recalculates the pError variable
    void calculateIError();       // Recalculates the iError variable
    void calculateDError();       // Recalculates the dError variable
};
