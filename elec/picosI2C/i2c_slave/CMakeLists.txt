cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico2 CACHE STRING "Board type")
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(picoSlave C CXX ASM)
pico_sdk_init()


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
    hardware_irq
)

add_executable(picoSlave picoSlave.c)

pico_enable_stdio_uart(picoSlave 1)
pico_enable_stdio_usb(picoSlave 1)

pico_add_extra_outputs(picoSlave)

target_compile_options(picoSlave PRIVATE -Wall)

target_link_libraries(picoSlave i2c_slave pico_stdlib)
