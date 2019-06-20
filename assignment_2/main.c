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

void handler();

int main() {

    struct sigaction action;
    action.sa_handler = handler;
    assert(sigemptyset(&action.sa_mask) >= 0);
    action.sa_flags = SA_RESTART;

    assert(sigaction(SIGUSR1, &action, NULL) == 0);
    assert(sigaction(SIGUSR2, &action, NULL) == 0);
    assert(sigaction(SIGURG, &action, NULL) == 0);
    
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
        assert((waitpid(-1, &status, 0)) != 0);
    }
    return(0);    
}

void handler(int signal_type) {
    if (signal_type == 10) {
        assert(printf("SIGUSR1 handled!\n") != 0);
    }
    if (signal_type == 12) {
        assert(printf("SIGUSR2 handled!\n") != 0);
    }
    if (signal_type == 23) {
        assert(printf("SIGURG handled!\n") != 0);
    }
}