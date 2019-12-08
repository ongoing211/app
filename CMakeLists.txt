cmake_minimum_required(VERSION 3.5)

project(ABDrawCMAKE LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package( OpenCV REQUIRED )

add_executable(ABDrawCMAKE
  main.cpp
  window.cpp
  window.h
  consts.h
  image.h
  window.ui
)


target_link_libraries(ABDrawCMAKE PRIVATE Qt5::Widgets ${OpenCV_LIBS})
