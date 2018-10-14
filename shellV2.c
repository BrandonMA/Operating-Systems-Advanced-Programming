#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <pwd.h>

// MARK: My own shell v2
int main(void) {

	while(1) {
		printf("0. Exit\n1. Create a file\n2. Read a file\n3. Change file permissions\n4. Change file owner\n5. Create a directory\n6. Remove a directory\n7. Create a symlink\n8. Read a symlink\n9. Change directory\n10. Rename file\n11. Move a file\n12. Remove a file\nShell ->    ");

		char answer[16];
	   	scanf("%s", answer);

	   	// Exit
	   	if (strcmp(answer, "0") == 0) {
	   		exit(0);
	   	}
	   	
	   	// Create a file
	   	if (strcmp(answer, "1") == 0) {
	   		printf("Write the pathname: "); // Ask the name
	   		char fileName[16]; // Makes a string to save the name
	   		scanf("%s", fileName); // Save the string
	   		int new = open(fileName, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR); // Create the file
	   		close(new); // Close the file
	   	} 

	   	// Read a file
	   	else if (strcmp(answer, "2") == 0) {
	   		printf("Write the pathname: "); // Ask the name
	   		char fileName[16]; // Makes a string to save the name
	   		scanf("%s", fileName); // Save the string

	   		char buffer[50]; // Creates a buffer to save information
	   		int fd = open(fileName, O_RDONLY); // Open the file that we want to read
	   		int new = open("new.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR); // Create a new file
	   		int nrd; // Save the code when you read
	   		while ((nrd = read(fd, buffer, 50))) {
	   			write(new, buffer, nrd); // Write the information inside new
	   		}
	   		close(fd); close(new); // Close both files
	   	} 

	   	// Change file permissions
	   	else if (strcmp(answer, "3") == 0) {
	   		printf("Write the pathname: "); // Ask the name
	   		char fileName[16]; // Make a string to save the name
	   		scanf("%s", fileName); // Save the string

	   		printf("Write the permissions: "); // Ask the mode
	   		char mode[16]; // Make a string to save the mode
	   		scanf("%s", mode); // Save the string

	   		int i; // Creates an integer with permissions
	    	i = strtol(mode, 0, 8); // Transforms the mode to an int
	    	if (chmod (fileName,i) < 0) {
	    		printf("There was an error changing permissions\n");
	        	exit(1);
	    	}
	   	} 

	   	// Change file owner
	   	else if (strcmp(answer, "4") == 0) {
	   		printf("Write the pathname: "); // Ask the name
	   		char fileName[16];
	   		scanf("%s", fileName);
	   		printf("Write the owner's name: "); // Ask the mode
	   		char owner[16];
	   		scanf("%s", owner);
	   		chown(fileName, getpwnam(owner)->pw_uid, -1);
	   	}

	   	// Create a directory
	   	else if (strcmp(answer, "5") == 0) {
	   		printf("Write the name: \n");
	   		char name[16];
	   		scanf("%s", name);
	   		mkdir(name, S_IRWXU | S_IRGRP | S_IXGRP); // Create the file with all rights for the user and rx to the group
	   	}

	   	// Remove a directory
	   	else if (strcmp(answer, "6") == 0) {
	   		printf("File's name: \n");
	   		char name[16];
	   		scanf("%s", name);
	   		rmdir(name); // Remove the file
	   	}

	   	// Create a symlink
	   	else if (strcmp(answer, "7") == 0) {
	   		printf("Write the pathname: "); // Ask the name
	   		char fileName[16];
	   		scanf("%s", fileName);
	   		printf("Write the symlink name: "); // Ask the name
	   		char name[16];
	   		scanf("%s", name);
	   		symlink(fileName, name); // Create the symlink
	   	}

	   	// Read a symlink
	   	else if (strcmp(answer, "8") == 0) {
	   		char path[128];
	        printf("Write the path: ");
	        scanf("%s", path);
	        char buffer[128];
	        readlink(path, buffer, 128);
	        printf("The content of the link is: %s\n", buffer); // Read the name-path that is inside the symlink
	   	}

	   	// Change directory
	   	else if (strcmp(answer, "9") == 0) {
	   		char path[128];
	        printf("Write the path: ");
	        scanf("%s", path);
	        chdir(path);
	   	}

	   	// Rename a file
	   	else if (strcmp(answer, "10") == 0) {
	   		char oldName[128];
	   		char newName[128];
	   		printf("File's name: ");
	   		scanf("%s", oldName);
	   		printf("Write the new name: ");
	   		scanf("%s", newName);
	   		rename(oldName, newName);
	   	}

	   	// Move a file
	   	else if (strcmp(answer, "11") == 0) {
	   		char oldName[128];
	   		char newName[128];
	   		printf("File's name: ");
	   		scanf("%s", oldName);
	   		printf("Write the new name: ");
	   		scanf("%s", newName);
	   		link(oldName, newName);
	   		remove(oldName);
	   	}

	   	// Remove a file
	   	else if (strcmp(answer, "12") == 0) {
	   		char path[128];
	        printf("Write the path: ");
	        scanf("%s", path);
	        remove(path);
	   	}

	}
}




























