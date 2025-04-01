
#include "env_utils.h"  


int main(int argc, char *argv[], char *envp[]) {
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
