cmake_minimum_required(VERSION 3.5)
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()
project(digidocshellextension VERSION 3.13.7)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include( GNUInstallDirs )
include( VersionInfo )

add_subdirectory( windows )
