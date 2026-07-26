# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)
list(APPEND app_sources ${CMAKE_SOURCE_DIR}/include/tinywav/tinywav.c)
list(APPEND app_sources ${CMAKE_SOURCE_DIR}/include/led_strip/led_strip_rmt_dev.c)
list(APPEND app_sources ${CMAKE_SOURCE_DIR}/include/led_strip/led_strip_rmt_encoder.c)
list(APPEND app_sources ${CMAKE_SOURCE_DIR}/include/led_strip/led_strip_api.c)

idf_component_register(
    SRCS ${app_sources}
    REQUIRES esp_driver_i2c
)
