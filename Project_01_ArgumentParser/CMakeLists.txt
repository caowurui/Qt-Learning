cmake_minimum_required(VERSION 3.16)
project(Project_01_ArgumentParser)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# 查找Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Test)

# ---- 主程序 ----
file(GLOB MAIN_SOURCES "src/*.cpp")
list(REMOVE_ITEM MAIN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/tests/test.cpp")

# 创建主程序可执行文件
add_executable(${PROJECT_NAME}
    ${MAIN_SOURCES}
    src/ArgumentParser.h
)

# 启用Qt的元对象编译器（MOC）
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
)

# 链接Qt6库
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)

# 设置包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ---- 测试程序 ----
add_executable(${PROJECT_NAME}_tests
    src/tests/test.cpp
    src/ArgumentParser.h
    src/ArgumentParser.cpp
)

set_target_properties(${PROJECT_NAME}_tests PROPERTIES
    AUTOMOC ON
)

target_link_libraries(${PROJECT_NAME}_tests PRIVATE Qt6::Core Qt6::Test)

target_include_directories(${PROJECT_NAME}_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 编译选项
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    target_compile_options(${PROJECT_NAME}_tests PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(${PROJECT_NAME}_tests PRIVATE -Wall -Wextra -pedantic)
endif()
