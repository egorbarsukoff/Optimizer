cmake_minimum_required(VERSION 3.5)

project(gui_qt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if (ANDROID)
    add_library(gui_qt SHARED
            main.cpp
            src/mainwindow.cpp
            include/gui/mainwindow.h
            src/mainwindow.ui
            )
else ()
    add_executable(gui_qt
            main.cpp
            include/gui/mainwindow.h
            include/gui/Plot.h
            src/mainwindow.cpp
            src/Plot.cpp src/DialogForm.cpp include/gui/DialogForm.h)
endif ()
target_include_directories(gui_qt PRIVATE include)
target_link_libraries(gui_qt PRIVATE Qt5::Widgets optimizer)
