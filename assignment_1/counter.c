#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char*argv[]) {
    char* end;
    long int number = strtol(argv[1], &end, 10);
    for (int i = 1; i <= number; i++){
        assert(printf("Process: %d %d\n", getpid(), i) != 0);
    }
    assert(printf("Process %d exited with status: %ld \n", getpid(), number) != 0);
    return(number);
}