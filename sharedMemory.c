#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define KEY 4566
#define PERMS 0660

int main(void) {

	int id;

	int *numbers;

  	id = shmget(KEY, 4 * sizeof(int), IPC_CREAT | PERMS);

  	numbers = (int *) shmat(id, NULL, 0);

  	if (fork() == 0) {
  		if (fork() == 0) {
  			numbers[1] = 2 + 4;
		} else {
			wait(NULL);
			numbers[2] = 4 - 1;
			numbers[0] = numbers[1] * numbers[2];
		}
	} else {
		wait(NULL);
		numbers[3] =  3 + 3;
		numbers[0] = numbers[0] + numbers[3];
		printf("%d\n", numbers[0]);
		shmctl(id, IPC_RMID, NULL);
	}
}
















