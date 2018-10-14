#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
 
#define SIZE 5
#define NUMB_THREADS 6
#define PRODUCER_LOOPS 1
 
 /* initially buffer will be empty.  full_sem
   will be initialized to buffer SIZE, which means
   SIZE number of producer threads can write to it.
   And empty_sem will be initialized to 0, so no
   consumer can read from buffer until a producer
   thread posts to empty_sem */
int buffer[SIZE];
int buffer_index;
 
pthread_mutex_t buffer_mutex; // Create a mutex so just 1 producer can insert or read a value at the same time
sem_t *full_sem;  // When is 0 then buffer is going to be full
sem_t *empty_sem; // When is 0 then buffer is going to be empty
 
void insertbuffer(int value) {
    if (buffer_index < SIZE) {
        buffer[buffer_index++] = value; // buffer_index++ return the current value and then increment it by 1
    } else {
        printf("Buffer overflow\n");
    }
}

int dequeuebuffer() {
    if (buffer_index > 0) {
        return buffer[--buffer_index]; // --buffer_index decrement the current value by 1 and then return it
    } else {
        printf("Buffer underflow\n");
    }
    return 0;
}

// MARK: Producer logic
void *producer(void *thread_n) {

    int thread_numb = *(int *)thread_n;
    int value;
    int i = 0;

    while (i++ < PRODUCER_LOOPS) {
        value = rand() % 100; // Generate a random value between 0 and 100
        sem_wait(full_sem); // if sem is 0 then wait else sem > 0 then go and decrement it
        
        /* possible race condition here. After this thread wakes up,
           another thread could aqcuire mutex before this one, and add to list.
           Then the list would be full again
           and when this thread tried to insert to buffer there would be
           a buffer overflow error */

        pthread_mutex_lock(&buffer_mutex); // Lock the mutex to insert the value
        insertbuffer(value);
        pthread_mutex_unlock(&buffer_mutex); // Unlock
        sem_post(empty_sem); // post (increment) empty_buffer semaphore so a consumer is able to read
        printf("Producer %d added %d to buffer\n", thread_numb, value);
    }
    pthread_exit(0); // End the thread
}
 
// MARK: Consumer logic
void *consumer(void *thread_n) {

    int thread_numb = *(int *)thread_n;
    int value;
    int i=0;

    while (i++ < PRODUCER_LOOPS) {
        sem_wait(empty_sem); // Wait for a producer to call sem_post
        /* there could be race condition here, that could cause
           buffer underflow error */
        pthread_mutex_lock(&buffer_mutex); // Lock the mutex to read the value
        value = dequeuebuffer();
        pthread_mutex_unlock(&buffer_mutex); // Unlock
        sem_post(full_sem); // post (increment) fullbuffer semaphore
        printf("Consumer %d dequeue %d from buffer\n", thread_numb, value);
   }
    pthread_exit(0); // End the thread
}
 
int main(int argc, char **argv) {

    buffer_index = 0;
 
    pthread_mutex_init(&buffer_mutex, NULL); // Initialize the mutex

    // full_sem is initialized to buffer size because SIZE number of producers can add one element to buffer each.
    // They will wait semaphore each time, which will decrement semaphore value.
    full_sem = sem_open("full_sem", O_CREAT, 0666, SIZE);
    //empty_sem is initialized to 0, because buffer starts empty and consumer cannot take any element from it.
    // They will have to wait until producer posts to that semaphore
    empty_sem = sem_open("empty_sem", O_CREAT, 0666, 0);

    pthread_t thread[NUMB_THREADS]; // Creates a table holding all threads
    int thread_numb[NUMB_THREADS]; // Creates a table holding thread's number

    int i; // Shared counter for both loops
    for (i = 0; i < NUMB_THREADS; ) {
        thread_numb[i] = i; // Save the number of the thread
        pthread_create(thread + i, NULL, producer, thread_numb + i);  // Creates a producer
        i++;
        thread_numb[i] = i;
        pthread_create(&thread[i], NULL, consumer, &thread_numb[i]); // Creates a consumer
        i++;
    }
 
    for (i = 0; i < NUMB_THREADS; i++) {
        pthread_join(thread[i], NULL); // Wait for each thread to end the program
    }
 
    pthread_mutex_destroy(&buffer_mutex); // Destroy the mutex
    // Close both semaphores
    sem_close(full_sem);
    sem_close(empty_sem);
 
    return 0;
}







