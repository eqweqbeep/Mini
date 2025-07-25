#include<stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

char *gnl(int fd) {
    static char buf[42];
    static int pos;
    static ssize_t r_ret;
    char *line = malloc(sizeof(char) * 1000000);
    int i = 0;
    while(1) {
        if(pos == r_ret) {
            r_ret = read(fd , buf ,42);
            pos = 0;
            if(r_ret <= 0)
                break;
        }
        line[i++] = buf[pos++];
        if(buf[pos - 1] == '\n')
            break;
    }
    line[i] = '\0';
    if(i == 0)
        return NULL;
    return line;
}


int main(int c ,char **v) {
   if 
         (c != 2) {write(2, "xxx\n", 4);}
    char *word = v[1];
    char *line;
}