
#include "env_utils.h"

void print_env_from_envp(char* envp[]) {
    for (char** env = envp; *env; env++) {
        printf("%s\n", *env);
    }
}

void print_env_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open env file");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        char* value = getenv(buffer);
        if (value) {
            printf("%s=%s\n", buffer, value);
        }
    }

    fclose(file);
}


int child_counter = 0;

void spawn_child(const char *child_path, char mode, char **child_env) {
    if (child_counter >= 100) {
        printf("Maximum child processes (99) reached.\n");
        return;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return;
    } else if (pid == 0) {  
        char child_exec[BUFFER_SIZE];
        snprintf(child_exec, sizeof(child_exec), "%s/child", child_path);

        char child_name[16];
        snprintf(child_name, sizeof(child_name), "child_%02d", child_counter);

        if (mode == '+') {
            execl(child_exec, child_name, ENV_FILE, NULL);
        } else if (mode == '*') {
            execve(child_exec, (char *[]){child_name, NULL}, child_env);
        } else if (mode == '&') {
            // В случае &, передаем переменные окружения из файла env
            execve(child_exec, (char *[]){child_name, NULL}, child_env);
        }

        perror("execve failed");
        exit(EXIT_FAILURE);
    }

    child_counter++;
}

char **load_env_from_file() {
    FILE *file = fopen(ENV_FILE, "r");
    if (!file) {
        perror("Failed to open env file");
        return NULL;
    }

    char **new_env = malloc(MAX_ENV_VARS * sizeof(char *));
    if (!new_env) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file) && count < MAX_ENV_VARS - 1) {
        buffer[strcspn(buffer, "\n")] = 0;
        char *value = getenv(buffer);
        if (value) {
            char *entry = malloc(strlen(buffer) + strlen(value) + 2);
            if (entry) {
                sprintf(entry, "%s=%s", buffer, value);
                new_env[count++] = entry;
            }
        }
    }

    new_env[count] = NULL;
    fclose(file);
    return new_env;
}

void free_env(char **env) {
    if (env) {
        for (int i = 0; env[i]; i++) {
            free(env[i]);
        }
        free(env);
    }
}

void handle_keyboard(const char *child_path, char **child_env) {
    printf("Press + to spawn a child with file env, * to spawn with environment array, & to spawn with environment from file env, q to quit.\n");
    char ch;
    while (read(STDIN_FILENO, &ch, 1) > 0) {
        if (ch == 'q') break;
        if (ch == '+' || ch == '*' || ch == '&') {
            spawn_child(child_path, ch, child_env);
        }
    }
}
