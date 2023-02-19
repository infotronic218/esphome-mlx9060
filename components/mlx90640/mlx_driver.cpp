#include"esphome.h"
#include "mlx_driver.h"

namespace esphome {
    namespace mlx90640{
        // Read a number of words from startAddress. Store into Data array.
// Returns 0 if successful, -1 if error
int MLX90640_Driver::MLX90640_I2CRead(uint8_t _deviceAddress, unsigned int startAddress,
                     unsigned int nWordsRead, uint16_t *data) {
    // Caller passes number of 'unsigned ints to read', increase this to 'bytes
    // to read'
    uint16_t bytesRemaining = nWordsRead * 2;

    // It doesn't look like sequential read works. Do we need to re-issue the
    // address command each time?

    uint16_t dataSpot = 0;  // Start at beginning of array

    // Setup a series of chunked I2C_BUFFER_LENGTH byte reads
    while (bytesRemaining > 0) {
        Wire.beginTransmission(_deviceAddress);
        Wire.write(startAddress >> 8);         // MSB
        Wire.write(startAddress & 0xFF);       // LSB
        if (Wire.endTransmission(false) != 0)  // Do not release bus
        {
            Serial.println("No ack read");
            return (0);  // Sensor did not ACK
        }

        uint16_t numberOfBytesToRead = bytesRemaining;
        if (numberOfBytesToRead > I2C_BUFFER_LENGTH)
            numberOfBytesToRead = I2C_BUFFER_LENGTH;

        Wire.requestFrom((uint8_t)_deviceAddress, numberOfBytesToRead);
        if (Wire.available()) {
            for (uint16_t x = 0; x < numberOfBytesToRead / 2; x++) {
                // Store data into array
                data[dataSpot] = Wire.read() << 8;  // MSB
                data[dataSpot] |= Wire.read();      // LSB

                dataSpot++;
            }
        }

        bytesRemaining -= numberOfBytesToRead;

        startAddress += numberOfBytesToRead / 2;
    }
    
    return (0);  // Success
}



// Write two bytes to a two byte address
int MLX90640_Driver::MLX90640_I2CWrite(uint8_t _deviceAddress, unsigned int writeAddress,
                      uint16_t data) {
    Wire.beginTransmission((uint8_t)_deviceAddress);
    Wire.write(writeAddress >> 8);    // MSB
    Wire.write(writeAddress & 0xFF);  // LSB
    Wire.write(data >> 8);            // MSB
    Wire.write(data & 0xFF);          // LSB
    if (Wire.endTransmission() != 0) {
        // Sensor did not ACK
        Serial.println("Error: Sensor did not ack");
        return (-1);
    }
    
    
    uint16_t dataCheck;
    MLX90640_I2CRead(_deviceAddress, writeAddress, 1, &dataCheck);
    if (dataCheck != data) {
        // Serial.println("The write request didn't stick");
        return -2;
    }

    return (0);  // Success
      }
    }
}