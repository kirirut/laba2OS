#ifndef ENV_UTILS_H
#define ENV_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "env_utils.h"

// Вывод всех переменных окружения из envp
void print_env_from_envp(char* envp[]);

// Вывод переменных из файла с использованием getenv
void print_env_from_file(const char* filename);

// Константы
#define ENV_FILE "../src/env"       // Путь к файлу с переменными окружения
#define MAX_ENV_VARS 100            // Максимальное количество переменных окружения
#define BUFFER_SIZE 1024            // Размер буфера

// Глобальные переменные
extern char **environ;              // Указатель на окружение текущего процесса
extern int child_counter;           // Счётчик дочерних процессов

// Создание дочернего процесса с заданным режимом и окружением
void spawn_child(const char *child_path, char mode, char **child_env);

// Загрузка окружения из файла в виде массива строк key=value
char **load_env_from_file();

// Освобождение памяти, выделенной под окружение
void free_env(char **env);

// Обработка ввода с клавиатуры для управления созданием процессов
void handle_keyboard(const char *child_path, char **child_env);

// Компаратор для сортировки строк окружения
int env_cmp(const void *a, const void *b);

#endif // ENV_UTILS_H
