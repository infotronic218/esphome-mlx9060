#include "mlx90640.h"

namespace esphome{
    namespace mlx90640{

        void MLX90640::setup(){
            // Initialize the the sensor data 
            //this->temperature_sensor = new sensor::Sensor();
            //this->min_temperature_sensor = new sensor::Sensor();
            //this->max_temperature_sensor = new sensor::Sensor();
            //this->min_index = new sensor::Sensor();
            //this->max_index = new sensor::Sensor();

        }

        void MLX90640::update(){
           // publish data to esphome
           this->temperature_sensor_->publish_state(10);
           this->min_temperature_sensor_->publish_state(10);
           this->max_temperature_sensor_->publish_state(20);
           //this->min_index->publish_state(40);
           //this->max_index->publish_state(60);

        }

    }
}