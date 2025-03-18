#!/bin/bash

# Проверка, что папка build существует
if [ ! -d "build" ]; then
    echo "Ошибка: папка build не найдена. Сначала выполните сборку проекта (./build.sh)."
    exit 1
fi

# Проверка, что программа parent существует
if [ ! -f "build/parent" ]; then
    echo "Ошибка: программа parent не найдена в папке build. Сначала выполните сборку проекта (./build.sh)."
    exit 1
fi

# Переход в папку build
cd build || { echo "Не удалось перейти в папку build"; exit 1; }

# Установка переменной окружения CHILD_PATH
export CHILD_PATH=./

# Запуск программы
echo "Запуск программы..."
./parent