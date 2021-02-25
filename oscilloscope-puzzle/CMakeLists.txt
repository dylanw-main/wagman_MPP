cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(puzzle_project)
pico_sdk_init()
add_executable(puzzle
    puzzle.c
)

pico_enable_stdio_usb(puzzle 1)
pico_enable_stdio_uart(puzzle 1)

pico_add_extra_outputs(puzzle)
target_link_libraries(puzzle pico_stdlib hardware_adc)