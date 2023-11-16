#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    char buf[BUF_SIZE];
    int status;

    while (1) {
        printf("simple_shell> ");
        fgets(buf, BUF_SIZE, stdin);

        if (strcmp(buf, "exit\n") == 0) {
            break;
        }

        pid_t child_pid = fork();

        if (child_pid == 0) {
            // Child process
            execlp(buf, NULL);
            exit(1);
        } else if (child_pid > 0) {
            // Parent process
            wait(&status);

            if (status != 0) {
                printf("Error: Command failed with status %d\n", status);
            }
        } else {
            // Error
            perror("fork");
            exit(1);
        }
    }

    return 0;
}

