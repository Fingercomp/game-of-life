cmake_minimum_required(VERSION 3.0)
project(GameOfLife)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(EXECUTABLE_NAME "game-of-life")

file(GLOB SRC_FILES
    "src/*.h"
    "src/*.hpp"
    "src/*.cpp"
)

add_executable(${EXECUTABLE_NAME} ${SRC_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules" ${CMAKE_SOURCE_PATH})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(SFML_STATIC_LIBRARIES TRUE)
endif()

find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  message(${SFML_LIBRARIES})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

message(${CMAKE_SYSTEM_NAME})
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

include_directories("${PROJECT_SOURCE_DIR}/src")

set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
