cmake_minimum_required(VERSION 3.16)
project(Project_04_MusicPlayer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# 查找Qt6
find_package(Qt6 REQUIRED COMPONENTS
    Core Gui Widgets Multimedia MultimediaWidgets)

set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/MusicPlayer.cpp
)

set(HEADERS
    src/MainWindow.h
    src/MusicPlayer.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Multimedia
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()
