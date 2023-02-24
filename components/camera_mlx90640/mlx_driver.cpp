#include"esphome.h"
#include "mlx_driver.h"
static const char * TAG = "MLXDriver";
namespace esphome {
    namespace mlx90640_app{

   MLXDriver::MLXDriver(TwoWire *wire){
            this->wire = wire;
    }
        // Read a number of words from startAddress. Store into Data array.
// Returns 0 if successful, -1 if error
int MLXDriver::MLX90640_I2CRead(uint8_t _deviceAddress, unsigned int startAddress,unsigned int nWordsRead, uint16_t *data) {
    // Caller passes number of 'unsigned ints to read', increase this to 'bytes
    // to read'
    uint16_t bytesRemaining = nWordsRead * 2;

    // It doesn't look like sequential read works. Do we need to re-issue the
    // address command each time?

    uint16_t dataSpot = 0;  // Start at beginning of array

    // Setup a series of chunked I2C_BUFFER_LENGTH byte reads
    while (bytesRemaining > 0) {
        this->wire->beginTransmission(_deviceAddress);
        this->wire->write(startAddress >> 8);         // MSB
        this->wire->write(startAddress & 0xFF);       // LSB
        if (this->wire->endTransmission(false) != 0)  // Do not release bus
        {
            ESP_LOGW(TAG,"No ack read");
            return (0);  // Sensor did not ACK
        }

        uint16_t numberOfBytesToRead = bytesRemaining;
        if (numberOfBytesToRead > I2C_BUFFER_LENGTH)
            numberOfBytesToRead = I2C_BUFFER_LENGTH;

        this->wire->requestFrom((int)_deviceAddress,(int) numberOfBytesToRead);
        if (this->wire->available()) {
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
int MLXDriver::MLX90640_I2CWrite(uint8_t _deviceAddress, unsigned int writeAddress,uint16_t data) {
    //this->i2cDev->write();
    this->wire->beginTransmission((uint8_t)_deviceAddress);
    this->wire->write(writeAddress >> 8);    // MSB
    this->wire->write(writeAddress & 0xFF);  // LSB
    this->wire->write(data >> 8);            // MSB
    this->wire->write(data & 0xFF);          // LSBe
    if (this->wire->endTransmission() != 0) {
        // Sensor did not ACK
        ESP_LOGW(TAG,"Error: Sensor did not ack");
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

     // Returns true if the MLX90640 is detected on the I2C bus.
// 如果在I2C总线上检测到MLX90640，则返回true
        boolean MLXDriver::isConnected(uint8_t addr) {
            this->wire->beginTransmission((uint8_t)addr);
            if (this->wire->endTransmission() != 0) return (false);  // Sensor did not ACK.
            return (true);
        }

      
    }
}