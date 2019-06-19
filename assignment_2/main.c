#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <assert.h>
#include <stdlib.h>

void handler();

int main() {

    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    assert(sigaction(SIGUSR1, &action, NULL) == 0);
    
    int status = fork();

    if (status == 0) {
        assert(execl("./child", "steve_da_best", NULL) != -1);
    }
    else if (status < 0) {
        perror("fork error");
        exit(-1);
    }
    else {
        assert((waitpid(-1, &status, 0)) != 0);
    }
    return(0);
    
}

void handler(int signal_type) {
    assert(printf("I made it here") != 0);
    if (signal_type == 10) {
        assert(printf("SIGUSR1 handled!") != 0);
    }
    if (signal_type == 12) {
        assert(printf("SIGUSR2 handled!") != 0);
    }
}