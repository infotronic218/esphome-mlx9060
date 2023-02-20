#ifndef __MLX_DRIVER__
#define __MLX_DRIVER__
#include "esphome.h"
#include <Wire.h>

namespace esphome{
    namespace mlx90640_app{
         class MLXDriver{
             private:
             TwoWire *wire;
             public:
             MLXDriver(TwoWire *wire);
             int MLX90640_I2CRead(uint8_t slaveAddr,  unsigned int startAddress, unsigned int nWordsRead, uint16_t *data);
             int MLX90640_I2CWrite(uint8_t slaveAddr, unsigned int writeAddress, uint16_t data);
             bool isConnected(uint8_t addr);
         };
    }
}

#endif