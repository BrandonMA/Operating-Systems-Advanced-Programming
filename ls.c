#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int ls(char *name) {

  struct stat fileStat;

  // Don't show hidden files
  if (name[0] == '.') {
    return 0;
  }

  if (stat(name,&fileStat) < 0) {
    printf("%s %s\n", strerror(errno), name);
    return 1;
  }

  // File Permissions
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("@ ");

    // Links
    printf("%d ",fileStat.st_nlink);

    // User Name
    struct passwd *pwd = getpwuid(fileStat.st_uid);
    printf("%s  ", pwd->pw_name);

    // Group Name
    struct group *g = getgrgid(fileStat.st_gid);
    printf("%s  ", g->gr_name);

    // File Size
    printf("%lld ",fileStat.st_size);

    // Last Modifitcation
    char date[20];
    strftime(date, 20, "%b %d %R", localtime(&(fileStat.st_ctime)));
    printf("%s ", date);

    // File Name
    printf("%s\n", name);

    return 0;
}

void readAll(char *fileName) {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (fileName)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir(dir)) != NULL) {
        if (fileName[0] != '.') {
          chdir(fileName);
        }

        ls(ent->d_name);

        // Don't show hidden files
      if (ent->d_name[0] != '.') {
        DIR *newDir;
        if ((newDir = opendir (ent->d_name)) != NULL) {
            closedir(newDir);
            readAll(ent->d_name);
        }
      }
      if (fileName[0] != '.') {
          chdir("..");
        }
      }
      closedir (dir);
  } else {
      ls(fileName);
  }
}

void removeAll(char *fileName) {

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(fileName)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {

            if (fileName[0] != '.') {
                chdir(fileName);
            }

            if (strcmp(ent->d_name, ".DS_Store") == 0) {
                remove(ent->d_name);
            }
            
            if (ent->d_name[0] != '.') {

                DIR *newDir;
                if ((newDir = opendir(ent->d_name)) != NULL) {
                    closedir(newDir);
                    removeAll(ent->d_name);
                } else {
                    remove(ent->d_name);
                }

                chdir("..");

                rmdir(ent->d_name);
            }

        }

        if (rmdir(fileName) != 0) {
            printf("%s\n", strerror(errno));
        }
        
    } else {
      remove(fileName);
    }
}


int main(int argc, char **argv) {

  if (argc != 3) {
        return 1;
  }

  if (strcmp(argv[2], "ls") == 0) {
    readAll(argv[1]);
  } else if (strcmp(argv[2], "rm") == 0) {
    removeAll(argv[1]);
  }

  
}






























