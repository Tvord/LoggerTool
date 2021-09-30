project(loggingtool)
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH /usr/lib64/)
include_directories (${CMAKE_BINARY_DIR})

# Make cross-version compiling by change only version
set(COMPILEDQTVERSION 4)
add_definitions( -DCOMPILEDQTVERSION=${COMPILEDQTVERSION} )

if(COMPILEDQTVERSION MATCHES "4")
    set(CMAKE_PREFIX_PATH /usr/lib64/qt4/)
    find_package(Qt4 4.8.7 REQUIRED QtCore)
    set(LIBRARY_OUTPUT_PATH lib/qt4/)
else()
    set(CMAKE_PREFIX_PATH /usr/lib64)
    find_package(Qt5 COMPONENTS Core)
    set(LIBRARY_OUTPUT_PATH lib/qt5/)
endif()

# End cross-version

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES LoggingTool.cpp LoggingTool.h)
#set(HEADERS main.cpp)

add_library(loggingtool STATIC ${SOURCES})# ${HEADERS})

if(COMPILEDQTVERSION MATCHES "4")
    target_link_libraries(loggingtool Qt4::QtCore)
else()
    target_link_libraries(loggingtool Qt5::Core)
endif()

link_directories(${CMAKE_SOURCE_DIR}/lib/qt4 ${CMAKE_SOURCE_DIR}/lib/qt5)
add_executable(example main.cpp)
target_link_libraries(example loggingtool)