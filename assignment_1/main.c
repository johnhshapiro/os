#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <assert.h>
#include <error.h>

int main() {
    int status = fork();
    int child_pid = getpid();
    int parent_pid = getppid();
    assert((waitpid(-1, &status, 0)) != 0);

    if (status == 0) {
        assert(printf("Child PID: %d\nParent PID: %d\n", child_pid, parent_pid) != 0);
        execl("./counter", "counter", "5", (char *) NULL);
    }
    else if (status < 0) {
        perror("fork error");
        exit(-1);
    }
    else {
    } 

    return 0;
}