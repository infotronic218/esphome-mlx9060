import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import sensor, text_sensor, i2c
from esphome.components import web_server_base
from esphome.components.web_server_base import CONF_WEB_SERVER_BASE_ID
from esphome.core import CORE, coroutine_with_priority
from esphome.const import (
    CONF_ID,
    CONF_TEMPERATURE,
    CONF_MIN_TEMPERATURE,
    CONF_MAX_TEMPERATURE,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    CONF_TIMEOUT,
    STATE_CLASS_MEASUREMENT,
    UNIT_METER, 
    ICON_ARROW_EXPAND_VERTICAL,
    #CONF_PIXEL_DATA
    
)

CONF_I2C_ADDRESS = "address"
CONF_SDA = "sda"
CONF_SCL = "scl"
CONF_FREQUENCY = "frequency"
CONF_PIXEL_DATA = "pixel_data"



DEPENDENCIES = ['esp32','web_server_base']

mlx90640_ns = cg.esphome_ns.namespace("mlx90640_app")
#MLX90640 = mlx90640_ns.class_("MLX90640", i2c.I2CDevice, cg.PollingComponent)
MLX90640 = mlx90640_ns.class_("MLX90640", cg.PollingComponent)
CONFIG_SCHEMA = (
    cv.Schema({
      cv.GenerateID(): cv.declare_id(MLX90640),
      cv.GenerateID(CONF_WEB_SERVER_BASE_ID): cv.use_id(
                web_server_base.WebServerBase
            ),
      cv.Optional(CONF_SCL):int,
      cv.Optional(CONF_SDA): int,
      cv.Optional(CONF_FREQUENCY):int ,
      cv.Optional(CONF_I2C_ADDRESS):int ,
      cv.Optional(CONF_PIXEL_DATA): text_sensor.text_sensor_schema(
               #name ="Pixel data"
            ),
      cv.Optional(CONF_MIN_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
    cv.Optional(CONF_MAX_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
    }).extend(cv.polling_component_schema("60s"))
    #.extend(i2c.i2c_device_schema(CONF_I2C_ADDR))
)


@coroutine_with_priority(45.0)
async def to_code(config):
    paren = await cg.get_variable(config[CONF_WEB_SERVER_BASE_ID])
    var = cg.new_Pvariable(config[CONF_ID], paren)
    await cg.register_component(var, config)
    #var =  cg.new_Pvariable(config[CONF_ID])
    #await cg.register_component(var, config)
    #await i2c.register_i2c_device(var, config)
    #cg.add(var.set_frequency(CONF_FREQUENCY))
    #cg.add(var.set_sda(CONF_SDA))
    #cg.add(var.set_scl(CONF_SCL))
    if CONF_PIXEL_DATA in config:
        conf = config[CONF_PIXEL_DATA]
        sens = await text_sensor.new_text_sensor(conf)
        cg.add(var.set_pixel_data_sensor(sens))

    if CONF_MIN_TEMPERATURE in config:
        conf = config[CONF_MIN_TEMPERATURE]
        sens = await sensor.new_sensor(conf)
        cg.add(var.set_min_temperature_sensor(sens))

    if CONF_MAX_TEMPERATURE in config:
        conf = config[CONF_MAX_TEMPERATURE]
        sens = await sensor.new_sensor(conf)
        cg.add(var.set_max_temperature_sensor(sens))
        
    if CONF_I2C_ADDRESS in config:
        addr = config[CONF_I2C_ADDRESS]
        cg.add(var.set_addr(addr))
    if CONF_SDA in config:
        sda = config[CONF_SDA]
        cg.add(var.set_sda(sda))
    if CONF_SCL in config:
        scl = config[CONF_SCL]
        cg.add(var.set_scl(scl))
    if CONF_FREQUENCY in config:
        freq = config[CONF_FREQUENCY]
        cg.add(var.set_frequency(freq))



