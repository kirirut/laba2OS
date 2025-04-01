#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "env_utils.h"  

extern char** environ;

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
