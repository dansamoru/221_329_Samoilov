cmake_minimum_required(VERSION 3.29)
project(exam)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(exam main.cpp
        src/transactionmodel.cpp
        src/transactionmodel.h
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.cpp
        src/addtransactiondialog.cpp
        src/addtransactiondialog.h)
target_link_libraries(exam
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

