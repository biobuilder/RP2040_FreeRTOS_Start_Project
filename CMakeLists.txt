cmake_minimum_required(VERSION 3.21)
include(pico_sdk_import.cmake)
include(pico_extras_import_optional.cmake)

# set project name to be the source directory folder
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
# you may change the project name to a specific value, such as MYPROJECT, by simply writing it in place of ${ProjectId}
project( ${ProjectId}       C CXX ASM)  # set project name and viable languages

# set c/c++ compiler standards 
set(CMAKE_C_STANDARD    11)
set(CMAKE_CXX_STANDARD  17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# initialize the sdk
pico_sdk_init()

add_compile_options(-Wall
                    -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
                    -Wno-unused-function # we have some for the docs that aren't called
                    )

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()


# freertos specific configurations
# make sure this variable points to the source code for the FreeRTOS Kernel
# for some reason, environment variables (in CMake settings in Visual Studio Code) are not able to configure this variable
# neither does the build argument in CMake settings:
# -DFREERTOS_KERNEL_PATH="E:/path/to/FreeRTOS-Kernel"
# instead, uncomment the line below to create a local defintition of the kernel path
set(FREERTOS_KERNEL_PATH "E:/source/project-repos/cloned-projects/FreeRTOS-Kernel" CACHE PATH "Path to the FreeRTOS Kernel")

# set the FreeRTOS configuration file directory
# make sure this variable points to the folder containing FreeRTOSConfig.h
set(FREERTOS_CONFIG_FILE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/src" CACHE STRING "Local Config")
include_directories("${FREERTOS_CONFIG_FILE_DIRECTORY}") # FreeRTOS config files

# include all other external libraries and dependencies
include(FreeRTOS_Kernel_import.cmake)


# add all project directories
add_subdirectory(src)
# if you added another directory, such as to a library (.c and .h files), you need to tell CMake where to look for it
# also, you need to update the specific CMakeLists.txt file for each new library
# add_subdirectory(mylibrary)
