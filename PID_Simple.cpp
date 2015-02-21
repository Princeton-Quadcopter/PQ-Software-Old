/* PID.cpp
 * Author: Lance Goodridge
 * Description: A really simple PID Controller.
 */

#include "PID.h"

/* Note about the gain constants + tuning:
 * Each of the gains (pGain, iGain, and dGain) are used to fine
 * tune the controller. pGain affects how much the current error
 * affects the output. iGain affects how much the previous errors
 * affect the output. dGain affects how much our predicted future
 * error will affect the output. iGain has the biggest effect on
 * the algorithm, followed by pGain, with dGain having a minimal
 * effect.
 * To tune the controller, set all the gains to zero, then
 * increment pGain and iGain together until an optimal value has
 * been found. Then, set dGain to one, and change iGain for big
 * adjustments, and dGain for smaller adjustments.
 */

// Constructor: constructs a new PID object
PID::PID(int interval, double pGain, double iGain, double dGain) :
interval(interval), pGain(pGain), iGain(iGain), dGain(dGain)
{
    value = 0.0;
    previousValue = 0.0;
    target = 0.0;
    pError = 0.0;
    iError = 0.0;
    dError = 0.0;
    for(int i = 0; i < 4; i++) {
        previousErrors[i] = 0.0;
    }
}

// Updates the data and recalculates the error variables
void PID::update(double newValue, double newTarget)
{
    previousValue = value;
    value = newValue;
    target = newTarget;
    calculatePError();
    calculateIError();
    calculateDError();
    updatePreviousErrors();
}

// Resets data and error values to zero. Starts taking new data
void PID::resetErrors()
{
    value = 0.0;
    previousValue = 0.0;
    target = 0.0;
    pError = 0.0;
    iError = 0.0;
    dError = 0.0;
    for(int i = 0; i < 4; i++) {
        previousErrors[i] = 0.0;
    }
}

/* Returns the controller output value
 * Note: This is a correction value, and must thus be
 * added to the current value to get the final output
 */
double PID::getOutput()
{
    return pGain * pError + iGain * iError + dGain * dError;
}

/* Updates the previousErrors array:
 * Shifts each member of the array back one, then adds the new
 * error at index 0
 */
void PID::updatePreviousErrors()
{
    previousErrors[3] = previousErrors[2];
    previousErrors[2] = previousErrors[1];
    previousErrors[1] = previousErrors[0];
    previousErrors[0] = pError;
}

/* Calculates the proportional error:
 * targetOutput - measuredOutput
 */
void PID::calculatePError()
{
    pError = target - value;
}

/* Calculates the integral error:
 * The integral can be approximated as the sum of rectangles
 * where the length is the average of the current and previous
 * errors and the width is change in time (interval variable)
 */
void PID::calculateIError()
{
    double average = (value + previousValue) / 2.0;
    iError = iError + (average * interval);
}

/* Calculates the derivative error:
 * The derivative can be approximated as follows:
 * D(e) = [e(i) + 3e(i-1) - 3e(i-2) - e(i-3)] / 6
 * where i is the index of the current error value.
 * NOTE: our indexes increment because that is how
 * it was implemented in the previousErrors array
 */
void PID::calculateDError()
{
    dError = (previousErrors[0] + 3.0 * previousErrors[1]
              - 3.0 * previousErrors[2] - previousErrors[3]) / 6.0;
}
