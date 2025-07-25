# Créer une bibliothèque au lieu d'un exécutable
add_library(squarewave_lib STATIC squarewave.c)

# fichier d'entête PIO
pico_generate_pio_header(squarewave_lib ${CMAKE_CURRENT_LIST_DIR}/squarewave.pio)

target_link_libraries(squarewave_lib PUBLIC
    pico_stdlib
    hardware_pio
    hardware_irq
)

# Expose include directory
target_include_directories(squarewave_lib PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)
