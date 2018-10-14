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

void listenForMessage(int newsockfd) {
    while(1) {
        char buffer[256]; // Buffer to save information from the client
        int n; // Contains the number of bytes read or written

        n = read(newsockfd,buffer,255); // Read from the socket
        if (n < 0) {
            error("ERROR reading from socket");
        }
        printf("Received Message -----> %s\n", buffer);
    }
}

void sendMessage(int newsockfd) {
	while(1) {
		char buffer[256]; // Buffer to save information from the client
		int n; // Contains the number of bytes read or written
		fgets(buffer,255,stdin);

		n = write(newsockfd, buffer, 32);
		if (n < 0) {
			error("ERROR writing to socket");
		}
	}
}

int main(int argc, char *argv[]) {

    int sockfd, newsockfd; // This two variables store the values returned by the socket system call and accept system call
    int portno; // Store the port number on which the server accepts connections
    socklen_t clilen; // Store the size of the address of the client
    char buffer[256]; // Buffer to save information from the client
    struct sockaddr_in serv_addr, cli_addr; // serv_addr containts the address of the server, cli_addr contains the address of the client

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
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); // Block the process until a connection starts

	if (newsockfd < 0) {
    	error("ERROR on accept");
	}

	if (fork() == 0){
		sendMessage(newsockfd);
	}
	else if (fork() == 0){
		listenForMessage(newsockfd);
	}

	wait(NULL);
	wait(NULL);

	close(newsockfd);
	close(sockfd);

	return 0;
}




















