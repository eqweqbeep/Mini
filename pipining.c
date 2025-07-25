/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipining.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 23:28:40 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/24 23:38:26 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// void open_in_out(int c, char **v) {
    // int in = open("file1" , O_RD)
// }



int main(int c, char **v , char **env) {
    int i = 0;
    int pid1 , pid2;
    int fd[2];
    int read_end = fd[0];
    int write_end = fd[1];
    // open_in_out(c , v);
    if(pipe(fd)  == -1)
        printf("pipe error \n");
    pid1 = fork();
    if(pid1 == 0) {
        dup2(write_end , 1);
        close(write_end);
        execute(v[1]);
    }
    pid2 = fork();
    
        
}