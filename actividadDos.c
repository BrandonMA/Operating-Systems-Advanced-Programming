#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {

	// MARK: -------- fork section --------

	// pid_t  pid;

 //    pid = fork();

 //    int i = 5;

 //    int * pointer = &i;

 //    if (pid == -1) {
 //    	printf("There was an error creating the process\n");
 //    	exit(EXIT_FAILURE); // This exit the process
 //    } else if (pid == 0) {
 //    	// This code run at the end
 //    	printf("I’m the child, my process id is: %d, and my parent's id is: %d \n", getpid(), getppid());
 //    	i++;
 //    	printf("%d\n", i);
 //    	_exit(0); // This exit the child process
 //    } else {
 //    	sleep(2); // sleep for 3 seconds
 //    	printf("I’m the parent, my process id is: %d\n", getpid());
 //  		printf("%d\n", i);
 //    }

	// MARK: -------- exec section --------

	pid_t pid = fork();
	int i = 5;

	// run an application
	// execlp("/usr/bin/open", "open", "-a", "Whatsapp", NULL);

	if (pid == -1) {
    	// error, failed to fork()
    	exit(EXIT_FAILURE);
    } else if (pid == 0) {
    	printf("This is the child process\n");

    	// write an exec call
    	execlp("/usr/bin/open", "open", "-a", "Safari", NULL);
        i++;
        printf("%d\n", i);
    }

	return 0;
}