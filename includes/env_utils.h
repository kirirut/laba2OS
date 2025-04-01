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
void print_env_from_envp(char* envp[]);
void print_env_from_file(const char* filename);


#define ENV_FILE "../src/env"
#define MAX_ENV_VARS 100
#define BUFFER_SIZE 1024

extern char **environ;
extern int child_counter;

void spawn_child(const char *child_path, char mode, char **child_env);
char **load_env_from_file();
void free_env(char **env);
void handle_keyboard(const char *child_path, char **child_env);

#endif // ENV_UTILS_H
