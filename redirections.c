#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {

	int textOne = open("text1.txt", O_RDONLY);

	if (textOne < 0) {
		return 1;
	}

	int textTwo = open("text2.txt", O_WRONLY);

	if (textTwo < 0) {
		return 1;
	}

	dup2(textTwo, fileno(stdout));

	char buffer[256]; // Creates a buffer to save information

	int n;
	while ((n = read(textOne, buffer, 256))) {
		write(fileno(stdout), buffer, n);
	}
	
	close(textOne);
	close(textTwo);

	return 0;
}