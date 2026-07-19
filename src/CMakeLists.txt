# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)
list(APPEND app_sources ${CMAKE_SOURCE_DIR}/include/tinywav/tinywav.c)
list(APPEND app_sources ${CMAKE_SOURCE_DIR}/include/spellcasting_v1/edge-impulse-sdk/classifier/ei_run_classifier.h)
list(APPEND app_sources ${CMAKE_SOURCE_DIR}/include/spellcasting_v1/edge-impulse-sdk/porting/ei_classifier_porting.h)
list(APPEND app_sources ${CMAKE_SOURCE_DIR}/include/spellcasting_v1/model-parameters/model_metadata.h)

idf_component_get_requirements(esp-dsp)
idf_component_register(
    SRCS ${app_sources}
    INCLUDE_DIRS
    .
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/spellcasting_v1
)
idf_component_register(
    SRCS
    "main.cpp"

    # ... your other sources

    # CRITICAL: Your compiled model file
    "edge-impulse-export/tflite-model/tflite_learn_1034060_6_compiled.cpp"

    # Add the porting layer files we just created
    "edge-impulse-export/edge-impulse-sdk/porting/ei_classifier_porting.cpp"
    "edge-impulse-export/edge-impulse-sdk/porting/espressif/ESP32/ei_printf.cpp"
    "edge-impulse-export/edge-impulse-sdk/porting/espressif/ESP32/ei_malloc.cpp"
    "edge-impulse-export/edge-impulse-sdk/porting/espressif/ESP32/ei_sleep.cpp"

    # Rest of Edge Impulse SDK (all .cpp/.cc/.c files)
    "edge-impulse-export/edge-impulse-sdk/dsp/**/*.cpp"
    "edge-impulse-export/edge-impulse-sdk/dsp/**/*.cc"
    "edge-impulse-export/edge-impulse-sdk/tensorflow/lite/micro/**/*.cpp"
    "edge-impulse-export/edge-impulse-sdk/tensorflow/lite/micro/**/*.cc"
    "edge-impulse-export/edge-impulse-sdk/tensorflow/lite/kernels/**/*.cpp"
    "edge-impulse-export/edge-impulse-sdk/tensorflow/lite/kernels/**/*.cc"
    "edge-impulse-export/edge-impulse-sdk/tensorflow/lite/core/api/**/*.cpp"
    "edge-impulse-export/edge-impulse-sdk/tensorflow/lite/core/api/**/*.cc"
    "edge-impulse-export/edge-impulse-sdk/thirdparty/**/*.cpp"
    "edge-impulse-export/edge-impulse-sdk/thirdparty/**/*.cc"
    INCLUDE_DIRS
    "."
    "edge-impulse-export"
    "edge-impulse-export/edge-impulse-sdk"
    "edge-impulse-export/model-parameters"
    "edge-impulse-export/tflite-model"
)