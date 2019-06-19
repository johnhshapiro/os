#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {

    int status = fork();
    pid_t ppid = getppid();
    printf("%d\n", status);

    if (status == 0) {
        execl("./child", "steve_da_best", NULL);
    }
}