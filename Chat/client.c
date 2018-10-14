
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
	perror(msg);
	exit(0); 
}

void listenForMessage(int sockfd) {
    while(1) {
        char buffer[256]; // Buffer to save information from the client
        int n; // Contains the number of bytes read or written

        n = read(sockfd,buffer,255); // Read from the socket
        if (n < 0) {
            error("ERROR reading from socket");
        }
        printf("Received Message -----> %s\n", buffer);
    }
}

void sendMessage(int sockfd) {
    while(1) {
        char buffer[256]; // Buffer to save information from the client
        int n; // Contains the number of bytes read or written
        fgets(buffer,255,stdin);

        n = write(sockfd, buffer, 32);
        if (n < 0) {
            error("ERROR writing to socket");
        }
    }
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR connecting");
    }

    if (fork() == 0) {
        sendMessage(sockfd);
    }
    else if (fork() == 0) {
        listenForMessage(sockfd);
    }

    wait(NULL);
    wait(NULL);

    close(sockfd);

    return 0;
 }
















