cmake_minimum_required(VERSION 3.14)

project(lab2_1oop LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(lab2_1oop
  VectorException.h TestException.h MyVector.h main.cpp
)
target_link_libraries(lab2_1oop Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS lab2_1oop
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
