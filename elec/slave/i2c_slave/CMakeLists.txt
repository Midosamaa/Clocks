add_library(i2c_slave INTERFACE)

target_include_directories(i2c_slave
    INTERFACE
    ./include)

target_sources(i2c_slave
    INTERFACE
    i2c_slave.c
)

target_link_libraries(i2c_slave
    INTERFACE
    hardware_i2c
)

add_executable(slave_i2c_handler slave_i2c_handler.c)

pico_enable_stdio_uart(slave_i2c_handler 1)
pico_enable_stdio_usb(slave_i2c_handler 1)

pico_add_extra_outputs(slave_i2c_handler)

target_compile_options(slave_i2c_handler PRIVATE -Wall)

target_link_libraries(slave_i2c_handler i2c_slave pico_stdlib)
