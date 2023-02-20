#ifndef __MLX90640__
#define __MLX90640__
#include<esphome.h>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"
#include "mlx90640.h"
#include "mlx_api.h"
#include "mlx_driver.h"


namespace esphome {
    namespace mlx90640_app{
         class MLXDriver ;
         class MLXApi ;

         class MLX90640:public i2c::I2CDevice, public PollingComponent {
              private:
                uint8_t sda_ ;
                uint8_t scl_ ;
                int frequency_ ;
                MLXDriver *driver ;
                MLXApi *mlxApi ;
                sensor::Sensor *temperature_sensor_{nullptr};
                sensor::Sensor *min_temperature_sensor_{nullptr} ;
                sensor::Sensor *max_temperature_sensor_{nullptr};
                //sensor::Sensor *min_index ;
               // sensor::Sensor *max_index ;
              public:
               void setup() override ;
               void update() override ;
               void set_temperature_sensor(sensor::Sensor *t_sensor){this->temperature_sensor_= t_sensor;}
               void set_min_temperature_sensor(sensor::Sensor *ts){this->min_temperature_sensor_ = ts;}
               void set_max_temperature_sensor(sensor::Sensor *ts){this->max_temperature_sensor_= ts;};
               void set_sda(uint8_t sda){this->sda_ = sda ;}
               void set_scl(uint8_t scl){this->scl_ = scl ;}
               void set_frequency(int freq){this->frequency_ = freq ;}

               
        };
    }
}


#endif