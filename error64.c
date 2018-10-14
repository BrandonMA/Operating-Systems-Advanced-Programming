#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t tid[2];
int i = 65;

void* doMath(void *arg) {

    pthread_t id = pthread_self();

    if (pthread_equal(id,tid[0])) {
        int a = i;
        sleep(1);
        a++;
        i = a;
    }
    else if ((pthread_equal(id,tid[1]))) {
        int a = i;
        sleep(2);
        a--;
        i = a;
    }

    return NULL;
}

int main(int argc, char const *argv[]) {

    pthread_create(&(tid[0]), NULL, &doMath, NULL);
    pthread_create(&(tid[1]), NULL, &doMath, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    printf("%d\n", i);
    return 0;
}