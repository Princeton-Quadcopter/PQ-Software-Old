/* Title: IMU.h
 * Description: A simplified library for
 * interfacing with the MPU6050 IMU sensor.
 *
 * Hardware Req.: IMU is wired to 5V, GND,
 * SCA, SCL, and Interrupt pins on Arduino.
 * (Specific pin numbers may vary: on UNO
 * and MEGA, Int. pin is digital 2, and SCA
 * and SCL have their own dedicated pins.
 *
 * Software Req: Serial.begin() and Wire.begin()
 * were previously called.
 */
 
#pragma once

#include "I2Cdev.h"
#include "MPU6050.h"

class IMU
{
public:
    IMU(); // Constructor
    void reset();    // Performs a device reset on the IMU
    int getXAccel(); // Returns x-axis acceleration
    int getYAccel(); // Returns y-axis acceleration
    int getZAccel(); // Returns z-axis acceleration
    int getXGyro();  // Returns x-axis gyroscope orientation (in degrees)
    int getYGyro();  // Returns y-axis gyroscope orientation (in degrees)
    int getZGyro();  // Returns z-axis gyroscope orientation (in degrees)

private:
    MPU6050 mpu;            // I2Cdevlib MPU6050 object
    uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
    uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
    uint16_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64]; // FIFO storage buffer
    bool dmpReady = false;  // Set true if DMP init was successful
};
