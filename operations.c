#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>

pthread_t tid[4];

int numbers[4];
int i = 0;

sem_t *my_semaphore;
sem_t *my_secondSemaphore;


void* doSomething(void *arg) {

    pthread_t id = pthread_self();

    if (pthread_equal(id,tid[0])) {
        int a = 3 + 3;

        sem_wait(my_semaphore);
        numbers[i] = a;
        i++;
        sem_post(my_semaphore);

        sem_post(my_secondSemaphore);
    }
    else if ((pthread_equal(id,tid[1]))) {
        int b = 4 - 1;

        sem_wait(my_semaphore);
        numbers[i] = b;
        i++;
        sem_post(my_semaphore);

        sem_post(my_secondSemaphore);
    }
    else if ((pthread_equal(id,tid[2]))) {
        int c = 3 + 2;

        sem_wait(my_semaphore);
        numbers[i] = c;
        i++;
        sem_post(my_semaphore);

        sem_post(my_secondSemaphore);
    } 
    else if ((pthread_equal(id,tid[3]))) {
        sem_wait(my_secondSemaphore);
        sem_wait(my_secondSemaphore);
        numbers[3] = numbers[0] * numbers[1];
        sem_wait(my_secondSemaphore);
        numbers[3] = numbers[3] * numbers[2];
        printf("result = %d\n", numbers[3]);
    }

    return NULL;
}

int main(int argc, char const *argv[]) {

    my_semaphore = sem_open("my_semaphore", O_CREAT, 0666, 1); // Mutex
    my_secondSemaphore = sem_open("my_secondSemaphore", O_CREAT, 0666, 0);

    pthread_create(&(tid[0]), NULL, &doSomething, NULL);
    pthread_create(&(tid[1]), NULL, &doSomething, NULL);
    pthread_create(&(tid[2]), NULL, &doSomething, NULL);
    pthread_create(&(tid[3]), NULL, &doSomething, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);

    sem_close(my_semaphore);
    sem_close(my_secondSemaphore);

    return 0;
}