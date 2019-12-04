cmake_minimum_required(VERSION 3.5)

project(ActionTagger LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_BuildTests OFF CACHE INTERNAL "")


find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(json-develop)

add_executable(ActionTagger
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  interval.cpp
  interval.h
  type.h
  customwidget.cpp
  customwidget.h
  customwidgetsubaction.cpp
  customwidgetsubaction.h
)

#add_library(ActionTagger ...)

target_link_libraries(ActionTagger PRIVATE Qt5::Widgets nlohmann_json::nlohmann_json)
