#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t tid[2];
int i = 65;
sem_t *my_semaphore;

void* doMath(void *arg) {

    pthread_t id = pthread_self();

    int value;

    if (pthread_equal(id,tid[0])) {
        int a = i;
        a++;
        i = a;
        printf("thread one %d\n", i);
        sem_post(my_semaphore);
    }
    else if ((pthread_equal(id,tid[1]))) {
        sem_wait(my_semaphore);
        int a = i;
        a--;
        i = a;
        printf("thread two %d\n", i);
    }

    return NULL;
}

int main(int argc, char const *argv[]) {

    my_semaphore = sem_open("/mysemaphore", O_CREAT, S_IRUSR | S_IWUSR, 1);

    pthread_create(&(tid[0]), NULL, &doMath, NULL);
    pthread_create(&(tid[1]), NULL, &doMath, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    sem_close(my_semaphore);

    printf("Final %d\n", i);

    return 0;
}









