#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void mySystem(char *cmd) {
	if (fork() == 0) {
		if (execlp("bash", "bash", "-c", cmd, NULL) == 0) {
			printf("no deberia imprimirse\n");
		}
    }
}
// MARK: My own shell v1
int main(void) {
	printf("1- Read a file\n2- Change file permissions\n3- Change owner\n4- Create a directory\n5- Remove a directory\n6- Create a Symlink\n7- Stat\n8- Change Directory\n9- Rename a file\n10- Remove a file\n11- Process Status\n12- Send signal\n13- Quit\n");
	char answer[10];
	fgets(answer, 10, stdin);

	// Open a file
	if (strcmp(answer, "1\n") == 0) {

		char cmd[64];
		strcpy(cmd, "open ");
		char arg[32];

		printf("Filename: ");
		fgets(arg, 32, stdin);
		strcat(cmd, arg);

		mySystem(cmd);
	}

	// Change file permissions
	if (strcmp(answer, "2\n") == 0) {

		char cmd[64];
		strcpy(cmd, "chmod ");
		char permissions[32];

		printf("Permissions: ");
		scanf("%s", permissions);
		strcat(cmd, permissions);
		strcat(cmd, " ");

		char arg[32];
		printf("Filename: ");
		scanf("%s", arg);
		strcat(cmd, arg);
		
		mySystem(cmd);
	}

	if (strcmp(answer, "3\n") == 0) {
		char cmd[64];
		strcpy(cmd, "chown ");

		printf("Write the owner's name: "); // Ask the mode
	   	char owner[16];
	   	scanf("%s", owner);
	   	strcat(cmd, owner);
	   	strcat(cmd, " ");

		printf("Write the pathname: "); // Ask the name
	   	char fileName[16];
	   	scanf("%s", fileName);
	   	strcat(cmd, fileName);

	   	mySystem(cmd);
	}

	if (strcmp(answer, "4\n") == 0) {

		char cmd[64];
		strcpy(cmd, "mkdir ");

		printf("Write the pathname: "); // Ask the name
	   	char fileName[16];
	   	scanf("%s", fileName);
	   	strcat(cmd, fileName);

	   	mySystem(cmd);
	}

	if (strcmp(answer, "5\n") == 0) {

		char cmd[64];
		strcpy(cmd, "rmdir ");

		printf("Write the pathname: "); // Ask the name
	   	char fileName[16];
	   	scanf("%s", fileName);
	   	strcat(cmd, fileName);

	   	mySystem(cmd);
	}

	if (strcmp(answer, "6\n") == 0) {

		char cmd[64];
		strcpy(cmd, "ln -s ");

		printf("Write the pathname: "); // Ask the name
	   	char fileName[16];
	   	scanf("%s", fileName);
	   	strcat(cmd, fileName);
	   	strcat(cmd, " ");

	   	printf("Write the symlink name: "); // Ask the name
	   	char name[16];
	   	scanf("%s", name);
	   	strcat(cmd, name);

	   	mySystem(cmd);
	}

	if (strcmp(answer, "7\n") == 0) {
		char cmd[64];
		strcpy(cmd, "stat ");

		printf("Write the pathname: "); // Ask the name
	   	char fileName[16];
	   	scanf("%s", fileName);
	   	strcat(cmd, fileName);

	   	mySystem(cmd);
	}

	if (strcmp(answer, "8\n") == 0) {
		char cmd[64];
		strcpy(cmd, "cd ");

		printf("Write the pathname: "); // Ask the name
	   	char fileName[16];
	   	scanf("%s", fileName);
	   	strcat(cmd, fileName);

	   	mySystem(cmd);
	}

	if (strcmp(answer, "9\n") == 0) {
		char cmd[64];
		strcpy(cmd, "mv ");

		printf("Write the pathname: "); // Ask the name
	   	char fileName[16];
	   	scanf("%s", fileName);
	   	strcat(cmd, fileName);
	   	strcat(cmd, " ");

	   	printf("Write the new name: "); // Ask the name
	   	char newName[16];
	   	scanf("%s", newName);
	   	strcat(cmd, newName);

	   	mySystem(cmd);
	}

	if (strcmp(answer, "10\n") == 0) {
		char cmd[64];
		strcpy(cmd, "rm ");

		printf("Write the pathname: "); // Ask the name
	   	char fileName[16];
	   	scanf("%s", fileName);
	   	strcat(cmd, fileName);

	   	mySystem(cmd);
	}

	if (strcmp(answer, "11\n") == 0) {
		char cmd[64];
		strcpy(cmd, "ps aux | grep ");

		printf("Write the process name: "); // Ask the name
	   	char fileName[16];
	   	scanf("%s", fileName);
	   	strcat(cmd, fileName);

	   	mySystem(cmd);
	}

	if (strcmp(answer, "12\n") == 0) {
		char cmd[64];
		strcpy(cmd, "kill ");

		printf("Write the process id: "); // Ask the name
	   	char fileName[16];
	   	scanf("%s", fileName);
	   	strcat(cmd, fileName);

	   	mySystem(cmd);
	}

	if (strcmp(answer, "13\n") == 0) {
		exit(0);
	}
}








































