cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico2 CACHE STRING "Board type")
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(slave C CXX ASM)


# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(slave main.c)

target_link_libraries(slave PRIVATE
    pico_stdlib 
    hardware_irq 
    hardware_i2c
    squarewave_lib
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(slave 1)
pico_enable_stdio_uart(slave 0)

pico_add_extra_outputs(slave)

add_subdirectory(./squarewavePIO)
#add_subdirectory(./i2c_slave)