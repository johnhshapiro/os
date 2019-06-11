#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <assert.h>
#include <error.h>

int main() {
    int pid = fork();
    int child_pid = getpid();
    int parent_pid = getppid();
    int exitStatus;

    if(pid < 0) {
        perror("fork"); 
        exit(-1);
    }
    else if(pid == 0) {
        printf("Child PID: %d\nParent PID: %d\n", child_pid, parent_pid);
        execl("./counter", "counter", "5", (char *) NULL);
    }
    else {
    }
    waitpid(pid, &exitStatus, 0); 

    return 0;
}