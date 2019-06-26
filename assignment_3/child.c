#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = getpid();
    while (1) {
        printf("awake in %d\n", pid);
        sleep(1);
    }
    return(0);
}