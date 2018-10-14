#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t tid[3];
sem_t *my_semaphore;
sem_t *my_secondSemaphore;

void* doSomething(void *arg) {

    pthread_t id = pthread_self();

    if (pthread_equal(id,tid[0])) {
        sem_wait(my_semaphore);
        printf("thread 1\n");
        sem_post(my_secondSemaphore);
    }
    else if ((pthread_equal(id,tid[1]))) {
        sem_wait(my_secondSemaphore);
        printf("thread 2\n");
    }
    else if ((pthread_equal(id,tid[2]))) {
        printf("thread 3\n");
        sem_post(my_semaphore);
    }

    return NULL;
}

int main(int argc, char const *argv[]) {

    my_semaphore = sem_open("/my_semaphore", O_CREAT, 0666, 0);
    my_secondSemaphore = sem_open("/my_secondSemaphore", O_CREAT, 0666, 0);

    pthread_create(&(tid[0]), NULL, &doSomething, NULL);
    pthread_create(&(tid[1]), NULL, &doSomething, NULL);
    pthread_create(&(tid[2]), NULL, &doSomething, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    sem_close(my_semaphore);
    sem_close(my_secondSemaphore);

    return 0;
}







