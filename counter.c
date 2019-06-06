#include <stdlib.h>
#include <sys/types.h>

int main(char int_string[]) {
    int number = atoi(int_string);
    pid_t pid = getpid();
    for (int i = 1; i <= number; i++){
        printf("Process: ", number, " ", i);
    }
    return number;
}