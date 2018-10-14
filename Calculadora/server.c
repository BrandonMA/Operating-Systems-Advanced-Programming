#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) {
    perror(msg);
	exit(1);
}

void startCalculator(int newsockfd) {

	while(1) {
		char buffer[256]; // Buffer to save information from the client
		int n; // Contains the number of bytes read or written

		bzero(buffer,256); // Set the buffer to zero

		n = read(newsockfd,buffer,255); // Read from the socket
		if (n < 0) {
			error("ERROR reading from socket");
		}
		int a = atoi(buffer);

		n = read(newsockfd,buffer,255); // Read from the socket
		if (n < 0) {
			error("ERROR reading from socket");
		}
		int b = atoi(buffer);

		n = read(newsockfd,buffer,255); // Read from the socket
		if (n < 0) {
			error("ERROR reading from socket");
		}
		int answer = atoi(buffer);

		char result[32];

		if (answer == 1) {
			sprintf(result, "%d", a+b);
		} else if (answer == 2) {
			sprintf(result, "%d", a-b);
		} else if (answer == 3) {
			sprintf(result, "%d", a*b);
		} else if (answer == 4) {
			sprintf(result, "%d", a/b);
		}

		n = write(newsockfd, result, 32);
		if(n < 0) {
			error("ERROR writing to socket");
		}

		n = read(newsockfd,buffer,255); // Read from the socket
		if (n < 0) {
			error("ERROR reading from socket");
		}

		if (strcmp(buffer, "n") == 0) {
			close(newsockfd);
			exit(0);
		}
	}
}

int main(int argc, char *argv[]) {

    int sockfd, newsockfd; // This two variables store the values returned by the socket system call and accept system call
    int portno; // Store the port number on which the server accepts connections
    socklen_t clilen; // Store the size of the address of the client
    struct sockaddr_in serv_addr, cli_addr; // serv_addr containts the address of the server, cli_addr contains the address of the client
    pid_t pid;

	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0); // Creates a new socket, it takes three arguments, the first one takes the address domain of the socket(AF_INET is for internet access), the second one is the type of the socket, the third one is the protocol, it should be always 0

	if (sockfd < 0) {
   		error("ERROR opening socket");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr)); // Set the value of the buffer to zero

	portno = atoi(argv[1]); // The port number is passed here

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY; // IP address of the server, in this case is the same one of the current machine
	serv_addr.sin_port = htons(portno); // Set the port number with network byte order
	
	// Check if the socket is not already in use
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("ERROR on binding");
	}

	listen(sockfd,5); // Start listening for connections

	clilen = sizeof(cli_addr);

	while(1) {

		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); // Block the process until a connection starts

		if (newsockfd < 0) {
    		error("ERROR on accept");
		}

		pid = fork();

     	if (pid < 0){
         	error("ERROR on fork");
     	}

     	if (pid == 0)  {
     		printf("done\n");
     		close(sockfd);
        	startCalculator(newsockfd);
        	exit(0);
     	} else {
     		close(newsockfd);
     	}
	}

	return 0;
}




















