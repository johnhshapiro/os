#define _POSIX_C_SOURCE 200809L
#define errno (*__errno_location())
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "syscall.h"
#include "eye2eh.c"

void handler();

int main() {

    struct sigaction action;
    action.sa_handler = handler;
    assert(sigemptyset(&action.sa_mask) >= 0);
    action.sa_flags = SA_RESTART | SA_NOCLDSTOP;

    assert(sigaction(SIGCHLD, &action, NULL) == 0);
    
    int status = fork();

    if (status == 0) {
        execl("./child", "steve_da_best", NULL);
        printf("Execl failed with error number %d\n", errno);
        exit(-1);
    }
    else if (status < 0) {
        perror("fork error");
        exit(-1);
    }
    else {
        for(int i = 0; i < 5; i++) {
            WRITESTRING("STOP, CHILD!\n");
            assert(kill(status, SIGSTOP) == 0);
            sleep(2);
            WRITESTRING("CONTINUE, CHILD!\n");
            assert(kill(status, SIGCONT) == 0);
            sleep(2);
        }
        assert(kill(status, SIGINT) == 0);
        if (WIFSIGNALED(status)){
            int exit_status = WTERMSIG(status);
            assert(printf("Process %ld exited with status: %d \n", status, exit_status) != 0);
        }
        pause();
    }
    return(0);    
}

void handler(int signal_type) {
    if (signal_type == 17) {
        WRITESTRING("SIGCHLD birthed!\n");
    }
}