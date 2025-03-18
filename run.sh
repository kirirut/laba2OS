#!/bin/bash

# Проверка и создание папки build, если она отсутствует
if [ ! -d "build" ]; then
    echo "Папка build не найдена. Создание папки build..."
    mkdir build || { echo "Не удалось создать папку build"; exit 1; }
fi

# Переход в папку build
cd build || { echo "Не удалось перейти в папку build"; exit 1; }

# Сборка проекта
echo "Сборка проекта..."
cmake .. || { echo "Ошибка при выполнении cmake"; exit 1; }
make || { echo "Ошибка при выполнении make"; exit 1; }

# Установка переменной окружения CHILD_PATH
export CHILD_PATH=./

# Запуск программы
echo "Запуск программы..."
./parent