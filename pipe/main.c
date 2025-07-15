#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int counter , char **vectors) {
    int i = -1;
    int fd[2];
    int pid1 , pid2;
    while(i < counter -1) {
        if(pipe(fd[2]) == -1) {
            write(2,"error : pipe\n" , 14);
        }
        
        if(i > 1) {
            if()
        }
    }
}