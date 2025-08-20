cmake_minimum_required(VERSION 3.16)
project(QtDualCalculator_UIv2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets QUIET)
if(NOT Qt6_FOUND)
  find_package(Qt5 COMPONENTS Widgets REQUIRED)
  set(QT_LIB Qt5::Widgets)
else()
  set(QT_LIB Qt6::Widgets)
endif()

file(GLOB SRC_FILES
  src/*.cpp
  src/models/*.cpp
  src/controllers/*.cpp
  src/views/*.cpp
)

add_executable(QtDualCalculator_UIv2 ${SRC_FILES})
target_include_directories(QtDualCalculator_UIv2 PRIVATE src src/models src/controllers src/views)
target_link_libraries(QtDualCalculator_UIv2 PRIVATE ${QT_LIB})
