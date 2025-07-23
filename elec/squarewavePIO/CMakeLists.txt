cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico2 CACHE STRING "Board type")
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(squarewave C CXX ASM)


# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(squarewave)

# fichier d'entête PIO
pico_generate_pio_header(squarewave ${CMAKE_CURRENT_LIST_DIR}/squarewave.pio)
target_sources(squarewave PRIVATE
    squarewave.c
    )
target_link_libraries(squarewave PRIVATE
    pico_stdlib hardware_pio hardware_irq hardware_i2c
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(squarewave 1)
pico_enable_stdio_uart(squarewave 0)

pico_add_extra_outputs(squarewave)
