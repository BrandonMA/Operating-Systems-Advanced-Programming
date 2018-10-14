#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t tid[2];
int numbers[4];

void* doMath(void *arg) {

    pthread_t id = pthread_self();

    if (pthread_equal(id,tid[0])) {
        numbers[1] = 2 + 4;
    }
    else if ((pthread_equal(id,tid[1]))) {
        numbers[2] = 4 - 1;
        pthread_join(tid[0], NULL);
        numbers[0] = numbers[1] * numbers[2];
    }

    return NULL;
}

int main(int argc, char const *argv[]) {

    pthread_create(&(tid[0]), NULL, &doMath, NULL);
    pthread_create(&(tid[1]), NULL, &doMath, NULL);

    numbers[3] =  3 + 3;

    pthread_join(tid[1], NULL);
    
    numbers[0] = numbers[0] + numbers[3];
    printf("%d\n", numbers[0]);

    return 0;
}