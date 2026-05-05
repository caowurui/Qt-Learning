cmake_minimum_required(VERSION 3.16)
project(Project_03_ChatClient)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# 查找Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

# 添加源文件
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/ClientConnection.cpp
)

set(HEADERS
    src/MainWindow.h
    src/ClientConnection.h
)


# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
)

# 链接Qt6库
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)

# 设置包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 编译选项
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()
