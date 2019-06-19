#include <sys/types.h>
#include <signal.h>
#include <stdio.h>

int main() {
    printf("poopity scoop\n");
    kill(1, SIGINT);
}