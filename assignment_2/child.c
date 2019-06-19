#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <stdlib.h>

int main() {
    assert(kill(getppid(), SIGUSR1) == 0);
    assert(kill(getppid(), SIGUSR2) == 0);
    return(0);
}