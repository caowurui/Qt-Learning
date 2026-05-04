cmake_minimum_required(VERSION 3.16)
project(Project_03_ChatServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

set(SOURCES
    src/main.cpp
    src/ChatServer.cpp
)

set(HEADERS
    src/ChatServer.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Network)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()
