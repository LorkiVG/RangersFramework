cmake_minimum_required(VERSION 3.20)
project(RangersFramework)

set(CMAKE_CONFIGURATION_TYPES Release Debug)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_GENERATOR_PLATFORM Win32)

add_subdirectory(Framework/)

add_subdirectory(Injector/)