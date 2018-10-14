#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t tid[3];
sem_t *my_semaphore;
sem_t *my_secondSemaphore;
sem_t *my_thirdSemaphore;

void* doSomething(void *arg) {

    pthread_t id = pthread_self();

    if (pthread_equal(id,tid[0])) {
        sem_wait(my_semaphore);
        sem_wait(my_secondSemaphore);
        printf("one\n");
        sem_post(my_semaphore);
        sem_post(my_secondSemaphore);
    }
    else if ((pthread_equal(id,tid[1]))) {
        sem_wait(my_secondSemaphore);
        sem_wait(my_thirdSemaphore);
        printf("two\n");
        sem_post(my_secondSemaphore);
        sem_post(my_thirdSemaphore);
    }
    else if ((pthread_equal(id,tid[2]))) {
        sem_wait(my_thirdSemaphore);
        sem_wait(my_semaphore);
        printf("three\n");
        sem_post(my_thirdSemaphore);
        sem_post(my_semaphore);
    }

    return NULL;
}

int main(int argc, char const *argv[]) {

    my_semaphore = sem_open("/deadlock", O_CREAT, 0666, 1);
    my_secondSemaphore = sem_open("/deadlock2", O_CREAT, 0666, 1);
    my_thirdSemaphore = sem_open("/deadlock3", O_CREAT, 0666, 1);

    pthread_create(&(tid[0]), NULL, &doSomething, NULL);
    pthread_create(&(tid[1]), NULL, &doSomething, NULL);
    pthread_create(&(tid[2]), NULL, &doSomething, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    sem_close(my_semaphore);
    sem_close(my_secondSemaphore);
    sem_close(my_thirdSemaphore);

    return 0;
}