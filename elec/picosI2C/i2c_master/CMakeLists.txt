cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico2_w CACHE STRING "Board type")
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(picoMaster C CXX ASM)
pico_sdk_init()

add_executable(picoMaster picoMaster.c)

pico_enable_stdio_uart(picoMaster 1)
pico_enable_stdio_usb(picoMaster 1)

pico_add_extra_outputs(picoMaster)

target_compile_options(picoMaster PRIVATE -Wall)

target_link_libraries(picoMaster pico_stdlib hardware_i2c hardware_irq)
