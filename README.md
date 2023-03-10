# ESPHOME COMPONENT FOR MLX90640

This works is a intergration of the MLX90640 Pixel sensor into ESPHOME Framwork.

## Features 
The implemented features are :
* Converting the pixel array into bitmap file image 
* The Image is stored inside the ESP32 Flash using SPIFFS library
* Find the minimal temperature as esphome temperature sensor
* Find the maximal temperature as esphome temperature sensor
* Calcul the center temperature as esphome temperature sensor
* Calcul the average temperature as esphome temperature sensor 

## Example of configuration in esphome
* Include as external components in esphome configuration
``` yaml
external_components:
  - source: 
      type: local
      path: components
    components: [camera_mlx90640]

```

* Include as remote components on github 
``` yaml
external_components:
  - source: 
      type: git
      url: https://github.com/esphome/camera_mlx90640
      ref: main
    components: [camera_mlx90640]

```

* Adding the camera configuration 
``` yaml
camera_mlx90640:
  id: thermal_cam
  update_interval: 20s
  sda: 25  # I2C SDA PIN
  scl: 26  # I2C SCL PIN
  frequency: 400000  # I2C Clock Frequency
  address: 0x33 # MLX90640 Address
  mintemp: 24 # Minimal temperature for color mapping
  maxtemp: 35 # Maximal temperature for color mapping
  refresh_rate: 0x05 # For 16Hz or 0x04 for 8Hz
  filter_level: 10.0 # Level in degree of the filter. If there a difference above the level, the pixel is approximated by the average of the next two pixels
  min_temperature:
      name: "MLX90640 Min temperature"
  max_temperature:
      name: "MLX90640 Max temperature"
  mean_temperature:
      name: "MLX90640 Mean temperature"
  median_temperature:
      name: "MLX90640 Median temperature"

```

##  Configuration reference
Use the [camera_test.yaml](camera_test.yaml) file as a configuration example to test code.

## Dependencies 
The implementation requires the following components 
* webserver 

The webserver component is used to host the image from the pixel data.  The image is available at the wedserver root [/thermal-camera](/thermal-camera). If the webserver IP address is 192.168.1.32 then the image is available at 
[http://192.168.1.32/thermal-camera](http://192.168.1.32/thermal-camera) . Going to this URL will allway displayed the newly convverted image.


## Configuration example 
Use the [camera_test.yaml](camera_test.yaml) file as a configuration example to test code.

## Dependencies
The sources code depnends on the following libraries.
*  SPIFFS 
*  MLX90640_Driver 
*  MLX90640_API

## The converted Image result 
![images/thermal-camera.png](/images/thermal-camera.png)

Adding the image URL to HomeAssistant gives the above result.

## Monitoring the camera data inside HomeAssistant
![measurements.png](/images/measurements.png)

Monitoring the sensor data gives the figure above. The Min and Max reading contains some outliers results in some points. The measurements errors on these points is above 50 degree.

## Filtering the outliers in the sensor reading
The ***MLX90640_BadPixelsCorrection*** function provided in the ***MLX90640** is used to filter outliers pixel from the pixel data but it doesn't produce good results. 


## Desired features to be implemented 
* Improve the image conversion to work like a ESP32-CAM with streaming capability. 
* Improve the filtering results of pixel data to reduce the error in measurements. The filtering function ***MLX90640_BadPixelsCorrection*** provided by the ***MLX90640 API*** didn't improve the pixel data.


## References used during the code implementation
The following resources have been used during the code implementation. 
* MLX90640 Library from melexis  [https://github.com/melexis/mlx90640-library](https://github.com/melexis/mlx90640-library)

* MLX90640 from Sparkfun [https://github.com/sparkfun/SparkFun_MLX90640_Arduino_Example](https://github.com/sparkfun/SparkFun_MLX90640_Arduino_Example)

* Szymon Baczyński’s ESP Thermal Camera WebServer
[https://github.com/Samox1/ESP_Thermal_Camera_WebServer](https://github.com/Samox1/ESP_Thermal_Camera_WebServer)
* FLIR ESP32-CAM USING THE MELEXIS MLX90640 
[https://www.cloudacm.com/?p=4091](https://www.cloudacm.com/?p=4091)



