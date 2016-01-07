#include "Lidar360.h"

void Lidar360::initLidar(int btnA, int btnB)
{
    // Opens & joins the irc bus as master
    I2c.begin();

    // Waits to make sure everything is powered up before sending or receiving data
    delay(100);

    // Sets a timeout to ensure no locking up of sketch if I2C communication fails
    I2c.timeOut(50);

    _buttonA = btnA;
    _buttonB = btnB;

     // reset device to defaults for distance measurment
    llWriteAndWait(0x00,0x00);
}

void Lidar360::setLidarOffSet(int offSet)
{

}

// Write a register and wait until it responds with success
void Lidar360::llWriteAndWait(char myAddress, char myValue)
{
    uint8_t nackack = 100; // Setup variable to hold ACK/NACK resopnses

    while (nackack != 0)
    { // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
      nackack = I2c.write(LIDAR_LITE_ADDRESS,myAddress, myValue); // Write to LIDAR-Lite Address with Value
      delay(2); // Wait 2 ms to prevent overpolling
    }
}

byte Lidar360::llReadAndWait(char myAddress, int numOfBytes, byte arrayToSave[2])
{
    uint8_t nackack = 100; // Setup variable to hold ACK/NACK resopnses

    while (nackack != 0)
    { // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
      nackack = I2c.read(LIDAR_LITE_ADDRESS,myAddress, numOfBytes, arrayToSave); // Read 1-2 Bytes from LIDAR-Lite Address and store in array
      delay(2); // Wait 2 ms to prevent overpolling
    }
    return arrayToSave[2]; // Return array for use in other functions
}

/* ==========================================================================================================================================
Get 2-byte distance from sensor and combine into single 16-bit int
=============================================================================================================================================*/
int Lidar360::llGetDistance()
{
    byte myArray[2]; // array to store bytes from read function
    int distance;

    llWriteAndWait(0x00,0x04); // Write 0x04 to register 0x00 to start getting distance readings
    llReadAndWait(0x8f,2,myArray); // Read 2 bytes from 0x8f
    distance = (myArray[0] << 8) + myArray[1];  // Shift high byte [0] 8 to the left and add low byte [1] to create 16-bit int
    return distance;
}

/* ==========================================================================================================================================
Average readings from velocity and distance
int numberOfReadings - the number of readings you want to average (0-9 are possible, 2-9 are reccomended)
=============================================================================================================================================*/
int Lidar360::llGetDistanceAverage(int numberOfReadings)
{
    int sum = 0; // Variable to store sum

    if(numberOfReadings < 2)
    {
      numberOfReadings = 2; // If the number of readings to be taken is less than 2, default to 2 readings
    }

    for(int i = 0; i < numberOfReadings; i++)
    {
        sum = sum + llGetDistance(); // Add up all of the readings
    }
    sum = sum/numberOfReadings; // Divide the total by the number of readings to get the average
    return sum;
}
