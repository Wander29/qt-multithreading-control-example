cmake_minimum_required(VERSION 3.16)

project(QtThreadingExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(thread_ex
    main.cpp
    mainwindow.h
    mainwindow.cpp
    worker.h
    worker.cpp
)

target_link_libraries(thread_ex
    Qt::Core
    Qt::Gui
    Qt::Widgets
)
