#pragma once 
#include"esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
    namespace mlx90640{
         class MLX90640:public I2CDevice, public Component, public PollingComponent {
              public:
               void setup() override ;
               void update() override ;
        }
    }
}