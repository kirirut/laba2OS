#!/bin/bash

# Проверка, существует ли папка build
if [ -d "build" ]; then
    echo "Очистка папки build..."
    # Удаление всего содержимого папки build
    rm -rf build/* || { echo "Ошибка при удалении содержимого папки build"; exit 1; }
    echo "Папка build успешно очищена."
else
    echo "Папка build не существует. Очистка не требуется."
fi