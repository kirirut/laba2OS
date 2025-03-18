#!/bin/bash

# Путь к папке build (на уровень выше, чем scripts)
BUILD_DIR="../build"

# Проверка и создание папки build, если она отсутствует
if [ ! -d "$BUILD_DIR" ]; then
    echo "Папка build не найдена. Создание папки build..."
    mkdir -p "$BUILD_DIR" || { echo "Не удалось создать папку build"; exit 1; }
fi

# Переход в папку build
cd "$BUILD_DIR" || { echo "Не удалось перейти в папку build"; exit 1; }

# Сборка проекта
echo "Сборка проекта..."
cmake .. || { echo "Ошибка при выполнении cmake"; exit 1; }
make || { echo "Ошибка при выполнении make"; exit 1; }

echo "Сборка завершена успешно."