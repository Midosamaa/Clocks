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

# Créer une bibliothèque pour le module I2C handler
add_library(i2c_slave_handler STATIC slave_i2c_handler.c)

target_include_directories(i2c_slave_handler PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(i2c_slave_handler PUBLIC
    i2c_slave
    pico_stdlib
)
