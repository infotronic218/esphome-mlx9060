# ESPHOME COMPONENT FOR MLX9060


## How it works 
The the pixel image is computed and stored on the flash memory as a BMP file. And the webserver hosts the image file through en endpoint.

### The image url 
The image is can be visualize through the ESP32 IP address plus the URL as follow. 
[http://192.168.1.32/thermal-camera](http://192.168.1.32/thermal-camera) where *192.168.1.32* is the ESP32 IP address shown on the console.

### Image Update 
The image is updated at each update cycle of the components. The current implementation does not provide realtime data of the image such as a camera display.
* The  **update_interval** property in the configuration define time to compute new image. At each update called by ESPHOME, a new image is computed and stored to the flash.


## Configuration example 
Use the [camera_test.yaml](camera_test.yaml) file as a configuration example to test code.

## Dependencies
The sources code depnends on the following libraries.
* FS : opied to local folder to solve compilation error with esphome 
* SPIFFS : Copied to local folder to solve compilation error with esphome
*  MLX90640_Driver
*  MLX90640_API


## Further Improvement 
Right now the implementation uses the WebSever to host the image stored inside the Flash memory. The future implementation is to be able to stream the Image data such as the ESP32 Camera implementation.




