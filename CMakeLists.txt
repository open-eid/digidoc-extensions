cmake_minimum_required(VERSION 3.0)
if(POLICY CMP0043)
	cmake_policy(SET CMP0043 NEW)
endif()
if(POLICY CMP0063)
	cmake_policy(SET CMP0063 NEW)
endif()
project(digidocshellextension VERSION 3.13.6)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include( GNUInstallDirs )
include( VersionInfo )

add_subdirectory( windows )
