import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import  i2c
from esphome.const import CONF_DATA, CONF_SEND_EVERY
from esphome.const import CONF_ID
from esphome.core import CORE, coroutine_with_priority

DEPENDENCIES = ["i2c"]
AUTO_LOAD = ["json"]
mlx_90640_ns = cg.esphome_ns.namespace("mlx90640")
MLX90640 = mlx_90640_ns.class_("MLX90640",i2c.I2CDevice, cg.Component, cg.Controller)