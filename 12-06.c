#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t cpid;
    char buf[1024];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {   
        close(pipefd[1]); // Close unused write end

        // Read from pipe
        read(pipefd[0], buf, sizeof(buf));
        printf("Child (PID %d) received message: %s", getpid(), buf);

        close(pipefd[0]); // Close read end
        return 0;
    } else {           
        close(pipefd[0]); // Close unused read end

        // Get message from user
        printf("Parent (PID %d), enter a message: ", getpid());
        fgets(buf, sizeof(buf), stdin);

        // Write to pipe
        write(pipefd[1], buf, strlen(buf));

        close(pipefd[1]); // Close write end
        wait(NULL);       // Wait for child
        return 0;
    }
}
