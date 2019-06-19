#include <sys/types.h>
#include <signal.h>

int main(int ppid) {
    kill(ppid, SIGINT);
}