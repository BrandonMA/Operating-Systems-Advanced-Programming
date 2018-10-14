#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

char memory[16384];
int tblFlagPages[16384];
int pageTable[256];
int flagFrame[256];

void init(){
    int i;
    for(i = 0; i < 16384; i++){
        tblFlagPages[i] = 0;
    }
    for(i = 0; i < 256; i++){
        pageTable[i] = -1;
        flagFrame[i] = 0;
    }
}

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


int myAlloc(int size) {
    
    static int lastPage;
    int firstPage;
   
    int i, k, j; 
   
    int val = myContAlloc(size);
    if(val == -1){
        printf("Not allocated");
        return -1;
    } else {
        firstPage = val/64;
        lastPage = (val + (size - 1)) / 64;
      
        for(k = firstPage; k < lastPage; k++){
            if(pageTable[k] == -1){
                for(j = lastPage; j < 256 && flagFrame[k] != 0; j++){
                    if(j == 256){
                        printf("Error no more space");
                        return -1;
                    }

                    lastPage = j;
                    pageTable[k] = j;
                    flagFrame[k] = 1;
                    return j;
                }
            }
        }
   }
   
   return val
}

int main(){
    init();
    myAlloc(15);
    myAlloc(20);

    for (int i = 0; i < 40; i++){
       printf("%i %i\n", i, tblFlagPages[i]);
   }
}







