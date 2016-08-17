cmake_minimum_required(VERSION 2.6)
project(GameOfLife)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(EXECUTABLE_NAME "game-of-life")

file(GLOB SRC_FILES
    "src/*.h"
    "src/*.cpp"
)

add_executable(${EXECUTABLE_NAME} ${SRC_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_SOURCE_PATH})

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

find_package(Box2D 2 REQUIRED)
if(BOX2D_FOUND)
  include_directories(${BOX2D_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${BOX2D_LIBRARY})
endif()

include_directories("${PROJECT_SOURCE_DIR}/src")

set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
