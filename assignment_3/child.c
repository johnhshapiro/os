#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

int main() {
    pid_t pid = getpid();
    while (1) {
        assert(printf("awake in %d\n", pid) != 0);
        assert(sleep(1) >= 0);
    }
    return(0);
}