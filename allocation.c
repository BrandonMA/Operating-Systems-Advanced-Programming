#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int tblFlagPages[16384];

int myContAlloc(int size) {
    int i, j, k;
    for(i = 0; i < 16384; i++){
        if(tblFlagPages[i] == 0){
            for(j = i + 1; j < 16384 && j < i + size && tblFlagPages[j] == 0; j++);
                if (j == i + size) {

                    for(k = i; k < i +size; k++){
                        tblFlagPages[k] = 1;
                    }
                    return i;
                } else {
                    i = j;
                }
        }
    }
    return -1;
}