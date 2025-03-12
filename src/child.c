#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char** environ;

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

int main(int argc, char* argv[], char* envp[]) {
    printf("Child process: %s (PID: %d, PPID: %d)\n", argv[0], getpid(), getppid());

    if (argc > 1) {
        print_env_from_file(argv[1]);
    }
    else {
        print_env_from_envp(envp);
    }

    return EXIT_SUCCESS;
}