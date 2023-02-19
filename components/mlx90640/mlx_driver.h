#pragma once 
#include "esphome.h"
#include <Wire.h>

namespace esphome{
    namespace mlx90640{
         class MLX90640_Driver{
             public:
             int MLX90640_I2CRead(uint8_t slaveAddr,  unsigned int startAddress, unsigned int nWordsRead, uint16_t *data);
             int MLX90640_I2CWrite(uint8_t slaveAddr, unsigned int writeAddress, uint16_t data);
         };
    }
}