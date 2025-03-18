#!/bin/bash

# Путь к папке build (на уровень выше, чем scripts)
BUILD_DIR="../build"

# Проверка, существует ли папка build
if [ -d "$BUILD_DIR" ]; then
    echo "Очистка папки build..."
    # Удаление всего содержимого папки build
    rm -rf "$BUILD_DIR"/* || { echo "Ошибка при удалении содержимого папки build"; exit 1; }
    echo "Папка build успешно очищена."
else
    echo "Папка build не существует. Очистка не требуется."
fi