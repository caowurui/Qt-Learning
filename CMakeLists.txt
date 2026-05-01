cmake_minimum_required(VERSION 3.16)
project(Cpp_Learning)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# 指定MSVC版本的Qt路径
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.1/msvc2022_64")

# 包含所有子项目
add_subdirectory(Project_01_ArgumentParser)
add_subdirectory(Project_02_TextEditor)
# add_subdirectory(Project_03_ChatClient)
# add_subdirectory(Project_04_MusicPlayer)
# add_subdirectory(Project_05_TaskManager)
# add_subdirectory(Project_06_DatabaseClient)
# add_subdirectory(Project_07_GameEngine)
