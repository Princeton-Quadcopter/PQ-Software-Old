#include "IMU.h"
#include "Arduino.h"
#include "Wire.h"

/* Constructor: initializes a new MPU object  *
 * with our desired defaults. Prints an error *
 * message if something went wrong.           */
IMU::IMU()
{   
    // Set I2Cdev clock to 400kHz
    TWBR = 24;

    // Initialize the MPU
    mpu = new MPU6050();
    mpu.initialize();
    deviceStatus = mpu.dmpInitialize();

    // Set gyro offsets (todo)
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788);

    // If it worked...
    if (deviceStatus == 0)
    {
        Serial.println("Enabling IMU DMP");
        mpu.setDMPEnabled(true);

        Serial.println("Enabing IMU interrupt detection");
        attachInterrupt(0, dmpDataReady, RISING);

    }
    
    // TODO: Finish Initialization
}

// Performs a device reset on the IMU
void IMU::reset() {
    return mpu.reset();
}

// Returns x-axis acceleration
int IMU::getXAccel() {
    return mpu.getAccelerationX();
}

// Returns y-axis acceleration
int IMU::getYAccel() {
    return mpu.getAccelerationY();
}

// Returns z-axis acceleration
int IMU::getZAccel() {
    return mpu.getAccelerationZ();
}

// Returns x-axis gyroscope orientation (in degrees)
int IMU::getXGyro() {
    return mpu.getRotationX();
}

// Returns y-axis gyroscope orientation (in degrees)
int IMU::getYGyro() {
    return mpu.getRotationY();
}

// Returns z-axis gyroscope orientation (in degrees)
int IMU::getZGyro() {
    return mpu.getRotationZ();
}
