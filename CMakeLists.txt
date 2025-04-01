cmake_minimum_required(VERSION 3.24)
project(lab02 C)

set(CMAKE_C_STANDARD 11)

# Указываем правильный путь для заголовочных файлов
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Компилируем исполнимые файлы для parent и child
add_executable(parent src/parent.c src/env_utils.c)
add_executable(child src/child.c src/env_utils.c)
