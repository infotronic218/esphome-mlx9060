#pragma once 
#include "esphome.h"
#include <Wire.h>

namespace esphome{
    namespace mlx90640{
         class MLX90640_Driver{
             private:
             i2c::I2CDevice *i2cDev;
             public:
             MLX90640_Driver(i2c::I2CDevice *device);
             int MLX90640_I2CRead(uint8_t slaveAddr,  unsigned int startAddress, unsigned int nWordsRead, uint16_t *data);
             int MLX90640_I2CWrite(uint8_t slaveAddr, unsigned int writeAddress, uint16_t data);
         };
    }
}