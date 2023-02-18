import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import sensor, i2c
from esphome.const import (
    CONF_ID,
    CONF_TIMEOUT,
    STATE_CLASS_MEASUREMENT,
    UNIT_METER, 
    ICON_ARROW_EXPAND_VERTICAL,
)

CONF_I2C_ADDR = 0x57



DEPENDENCIES = ['i2c']

mlx90640_ns = cg.esphome_ns.namespace("mlx90640")
MLX90640 = mlx90640_ns.class_("MLX90640",sensor.Sensor, i2c.I2CDevice, cg.PollingComponent)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        MLX90640,
        unit_of_measurement=UNIT_METER,
        icon=ICON_ARROW_EXPAND_VERTICAL,
        accuracy_decimals=2,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(cv.polling_component_schema("60s")
    .extend(i2c.i2c_device_schema(CONF_I2C_ADDR)))
)


async def to_code(config):
    var =  cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
