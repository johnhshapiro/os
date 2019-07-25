
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

#define NUM_THREADS 20

pthread_mutex_t lock;

int i;

void *foo (void *bar) {
    printf("in a foo thread, ID %ld\n", (long) pthread_self());
    pthread_mutex_lock(&lock);

    for (i = 0; i < *((int *) bar); i++) {
        int tmp = i;

        if (tmp != i) {
            printf ("aargh: %d != %d\n", tmp, i);
        }
    }

    pthread_mutex_unlock(&lock);
    pthread_exit ((void *)pthread_self());
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("You must supply a numerical argument.\n");
        exit(1);
    }

    int iterations = strtol(argv[1], NULL, 10);
    assert(errno == 0);
    assert(iterations > 0);

    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, foo, (void *) &iterations)) {
            perror ("pthread_create");
            return (1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        void *status;
        if (pthread_join (threads[i], &status)) {
            perror ("pthread_join");
            return (1);
        }
        printf("joined a foo thread, number %ld\n", (long) status);
    }

    pthread_mutex_destroy(&lock);

    return (0);
}