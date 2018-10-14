#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {

  	int pipefd[2];

	// Try to create the pipe
  	if (pipe(pipefd) == -1) {
    	perror("pipe");
    	exit(EXIT_FAILURE);
	}

  	if (fork() == 0) {    /* Child reads from pipe */

		close(pipefd[0]);

		dup2(pipefd[1], fileno(stdout));

		execlp("ps", "ps", "aux", NULL);
    	
  	} else {

  		close(pipefd[1]);

  		if (fork() == 0) {

  			dup2(pipefd[0], fileno(stdin));

  			execlp("more", "more", NULL);

  		}

  		wait(NULL);
  		wait(NULL);

	} 
}




















