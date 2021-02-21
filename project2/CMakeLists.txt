cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(project2_project)
pico_sdk_init()
add_executable(project2
    project2.c
)
pico_enable_stdio_usb(project2 1)
pico_enable_stdio_uart(project2 1)
pico_add_extra_outputs(project2)
target_link_libraries(project2 pico_stdlib)