project(loggingtool)
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
include_directories (${CMAKE_BINARY_DIR})

set(COMPILEDQTVERSION 4)
add_definitions( -DCOMPILEDQTVERSION=${COMPILEDQTVERSION} )
set(LIBRARY_OUTPUT_PATH /opt/psatoolkit/lib64/qt${COMPILEDQTVERSION}/)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(COMPILEDQTVERSION MATCHES "4")
    set(CMAKE_PREFIX_PATH /usr/lib64/qt4/)
    find_package(Qt4 4.8.7 REQUIRED QtCore)
else()
    set(CMAKE_PREFIX_PATH /usr/lib64)
    find_package(Qt5 COMPONENTS Core)
endif()

set(SOURCES LoggingTool.cpp LoggingTool.h)
add_library(loggingtool.${COMPILEDQTVERSION} SHARED ${SOURCES})# ${HEADERS})

if(COMPILEDQTVERSION MATCHES "4")
    target_link_libraries(loggingtool.4 Qt4::QtCore)
else()
    target_link_libraries(loggingtool.5 Qt5::Core)
endif()
file(COPY LoggingTool.h DESTINATION /opt/psatoolkit/build/include/)

link_directories(${LIBRARY_OUTPUT_PATH})
add_executable(example main.cpp)
target_link_libraries(example loggingtool.${COMPILEDQTVERSION})