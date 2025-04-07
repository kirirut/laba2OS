#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <sys/wait.h>

#include "env_utils.h"

int main(int argc, char *argv[], char *envp[]) {
    // Установка локали для корректной сортировки по LC_COLLATE=C
    setenv("LC_COLLATE", "C", 1);
    setlocale(LC_COLLATE, "C");

    // Подсчёт переменных окружения
    int count = 0;
    while (envp[count]) count++;

    // Копируем переменные окружения
    char **env_copy = malloc((count + 1) * sizeof(char *));
    if (!env_copy) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; i++) {
        env_copy[i] = envp[i];  // Просто копируем указатели, а не строки
    }
    env_copy[count] = NULL;

    // Сортировка
    qsort(env_copy, count, sizeof(char *), env_cmp);

    // Вывод
    printf("=== Parent environment ===\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", env_copy[i]);
    }

    // Очистка
    free(env_copy);

    // Загрузка переменных окружения из файла
    char **child_env = load_env_from_file();
    if (!child_env) return EXIT_FAILURE;

    char *child_path = getenv("CHILD_PATH");
    if (!child_path) {
        fprintf(stderr, "CHILD_PATH not set\n");
        free_env(child_env);  // Free memory before exit
        return EXIT_FAILURE;
    }

    handle_keyboard(child_path, child_env);

    while (wait(NULL) > 0);
    printf("Parent exiting.\n");

    free_env(child_env);  // Free memory for child_env
    return EXIT_SUCCESS;
}
