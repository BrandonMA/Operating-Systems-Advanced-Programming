#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {

	if (fork() == 0) {

		int fd = open(argv[2], O_RDONLY);

		while(1) {
			char buffer[128];
			int n = read(fd, buffer, 128);
			write(1, buffer, n);
		}

	} else {

		int fd = open(argv[1], O_WRONLY);

		while(1) {
			char buffer[128];
			fgets(buffer, 127, stdin);
			write(fd, buffer, strlen(buffer) + 1);
		}
	}

    return 0;
	
}