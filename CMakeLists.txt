cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME prj_jlinktest_f411ve)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)


# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)
################################################################################
# 方法一：收集 custom 目录下的所有 .c 文件（推荐使用 CONFIGURE_DEPENDS）
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/User/LCD/*.c
    ${CMAKE_SOURCE_DIR}/LVGL/*.c  
    ${CMAKE_SOURCE_DIR}/LVGL/examples/porting/*.c
    ${CMAKE_SOURCE_DIR}/LVGL/src/*.c
    ${CMAKE_SOURCE_DIR}/LVGL/myGUI/generated/*.c    
    ${CMAKE_SOURCE_DIR}/LVGL/myGUI/generated/guider_customer_fonts/*.c
    ${CMAKE_SOURCE_DIR}/LVGL/myGUI/generated/guider_fonts/*.c
    ${CMAKE_SOURCE_DIR}/LVGL/myGUI/generated/images/*.c    


)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE 
    #Add user sources here
    ${MY_SOURCES}
)



# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/User
    ${CMAKE_SOURCE_DIR}/User/LCD
    ${CMAKE_SOURCE_DIR}/LVGL    
    ${CMAKE_SOURCE_DIR}/LVGL/examples/porting
    ${CMAKE_SOURCE_DIR}/LVGL/src
    ${CMAKE_SOURCE_DIR}/LVGL/custom
    ${CMAKE_SOURCE_DIR}/LVGL/myGUI/custom
    ${CMAKE_SOURCE_DIR}/LVGL/myGUI/generated
    ${CMAKE_SOURCE_DIR}/LVGL/myGUI/generated/guider_customer_fonts
    ${CMAKE_SOURCE_DIR}/LVGL/myGUI/generated/guider_fonts
    ${CMAKE_SOURCE_DIR}/LVGL/myGUI/generated/images

    # Add user defined include paths
)


################################################################################
# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
