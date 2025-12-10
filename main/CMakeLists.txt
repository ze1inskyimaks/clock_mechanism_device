idf_component_register(SRCS "clock_mechanism_device.c"
                        SRCS "esp-now_protocol/esp-now_protocol.c"
                        SRCS "temperature_sensor/temperature_sensor.c"

                    INCLUDE_DIRS "."
                    INCLUDE_DIRS "esp-now_protocol"
                    INCLUDE_DIRS "temperature_sensor"
)
