#ifndef __MLX90640__
#define __MLX90640__
#include<esphome.h>
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "mlx90640.h"
#include "mlx_api.h"
#include "mlx_driver.h"
#include <Wire.h>


namespace esphome {
    namespace mlx90640_app{
         class MLXDriver ;
         class MLXApi ;

         class MLX90640: public PollingComponent {
              private:
                TwoWire *wire ;
                uint8_t addr_ ;
                uint8_t sda_ ;
                uint8_t scl_ ;
                int frequency_ ;
                MLXDriver *driver ;
                MLXApi *mlxApi ;
                text_sensor::TextSensor *pixel_data_{nullptr};
                sensor::Sensor *min_temperature_sensor_{nullptr} ;
                sensor::Sensor *max_temperature_sensor_{nullptr};
                //sensor::Sensor *min_index ;
               // sensor::Sensor *max_index ;
              public:
               float get_setup_priority() const override { return esphome::setup_priority::BUS; }
               void setup() override ;
               void update() override ;
               void mlx_update() ;
               void set_pixel_data_sensor(text_sensor::TextSensor* t_sensor){this->pixel_data_= t_sensor;}
               void set_min_temperature_sensor(sensor::Sensor *ts){this->min_temperature_sensor_ = ts;}
               void set_max_temperature_sensor(sensor::Sensor *ts){this->max_temperature_sensor_= ts;};
               void set_addr(uint8_t addr){this->addr_ = addr;}
               void set_sda(uint8_t sda){this->sda_ = sda ;}
               void set_scl(uint8_t scl){this->scl_ = scl ;}
               void set_frequency(int freq){this->frequency_ = freq ;}

               
        };
    }
}


#endif