#/***************************************************************************
#                                                                           #
#    INORGANIC MATERIALS CHEMISTRY CONFIDENTIAL                             #
#                                                                           #
#    Copyright 2016 Inorganic Materials Chemistry                           #
#                   Eindhoven University of Technology (TU/e)               #
#                                                                           #
#    All Rights Reserved.                                                   #
#                                                                           #
#    NOTICE:  All information contained herein is, and remains              #
#    the property of Inorganic Materials Chemistry (TU/e) and its suppliers,#
#    if any.  The intellectual and technical concepts contained             #
#    herein are proprietary to Inorganic Materials Chemistry (TU/e)         #
#    and its suppliers and may be covered by U.S. and Foreign Patents,      #
#    patents in process, and are protected by trade secret or copyright law.#
#    Dissemination of this information or reproduction of this Materials    #
#    is strictly forbidden unless prior written permission is obtained      #
#    from Inorganic Materials Chemistry (TU/e).                             #
#                                                                           #
#    Authors: Ivo Filot       <i.a.w.filot@tue.nl>                          #
#             Emiel Hensen    <e.j.m.hensen@tue.nl>                         #
#                                                                           #
#****************************************************************************/

# set minimum cmake requirements
cmake_minimum_required(VERSION 2.8)
project (netris)

# add custom directory to look for .cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules )

# Enable release build
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# add OS specific
if(APPLE)
    add_definitions(-D_APPLE)
    add_definitions(-DEIGEN_NO_DEBUG)
    SET(BOOST_INCLUDEDIR "/opt/local/include")
    SET(BOOST_LIBRARYDIR "/opt/local/lib")
else()
    add_definitions(-DEIGEN_NO_DEBUG -Wno-literal-suffix)
    SET(BOOST_INCLUDEDIR "/usr/include")
    SET(BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu")
endif()

# set Boost
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

# Include libraries
find_package(glfw3 3.1 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost COMPONENTS chrono regex system serialization filesystem log thread REQUIRED)
pkg_check_modules(EIGEN eigen3 REQUIRED)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(PNG REQUIRED libpng)
pkg_check_modules(FREETYPE REQUIRED freetype2)

# Set include folders
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_BINARY_DIR}
                    ${Boost_INCLUDE_DIRS}
                    ${EIGEN_INCLUDE_DIRS}
                    ${FREETYPE_INCLUDE_DIRS})

# Add sources
file(GLOB_RECURSE SOURCES "*.cpp")
add_executable(netris ${SOURCES})

# Set C++11
add_definitions(-std=c++11)

# Link libraries
if(UNIX AND NOT APPLE)
    SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath=\$ORIGIN/lib")
endif()
if(APPLE)
    SET(CMAKE_MACOSX_RPATH TRUE)
    SET_TARGET_PROPERTIES(netris PROPERTIES INSTALL_RPATH "@executable_path/lib")
    SET(CMAKE_EXE_LINKER_FLAGS "-L${GLEW_LIBRARY_DIRS}")
    ADD_LIBRARY(lib_png STATIC IMPORTED)
    SET_TARGET_PROPERTIES(lib_png PROPERTIES IMPORTED_LOCATION ${PNG_STATIC_LIBRARY_DIRS}/lib${PNG_LIBRARIES}.a)
    ADD_LIBRARY(lib_freetype STATIC IMPORTED)
    SET_TARGET_PROPERTIES(lib_freetype PROPERTIES IMPORTED_LOCATION ${FREETYPE_STATIC_LIBRARY_DIRS}/libfreetype.a)
    ADD_LIBRARY(lib_z STATIC IMPORTED)
    SET_TARGET_PROPERTIES(lib_z PROPERTIES IMPORTED_LOCATION ${FREETYPE_STATIC_LIBRARY_DIRS}/libz.a)
    ADD_LIBRARY(lib_bz2 STATIC IMPORTED)
    SET_TARGET_PROPERTIES(lib_bz2 PROPERTIES IMPORTED_LOCATION ${FREETYPE_STATIC_LIBRARY_DIRS}/libbz2.a)
    ADD_LIBRARY(lib_glew STATIC IMPORTED)
    SET_TARGET_PROPERTIES(lib_glew PROPERTIES IMPORTED_LOCATION ${GLEW_STATIC_LIBRARY_DIRS}/lib${GLEW_STATIC_LIBRARIES}.a)
    target_link_libraries(netris glfw ${GLFW3_LIBRARY} ${X11_Xinerama_LIB} ${X11_Xrandr_LIB} ${X11_Xcursor_LIB} ${OPENGL_glu_LIBRARY} ${Boost_LIBRARIES} lib_png lib_freetype lib_z lib_bz2 lib_glew pthread dl)
else()
    target_link_libraries(netris glfw ${GLFW3_LIBRARY} ${X11_Xinerama_LIB} ${X11_Xrandr_LIB} ${X11_Xcursor_LIB} ${OPENGL_glu_LIBRARY} ${GLEW_STATIC_LIBRARIES} ${Boost_LIBRARIES} ${PNG_LIBRARIES} ${FREETYPE_LIBRARIES} pthread dl)
endif()

# add Boost definition
add_definitions(-DBOOST_LOG_DYN_LINK)

# add Wno-literal-suffix to suppress warning messages
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")

###
# Installing
##
install (TARGETS netris DESTINATION bin)
