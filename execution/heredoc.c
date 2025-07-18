/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/06/01 17:21:12 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
// // the base of herdoc is [n] << [-]Word
// //              here_document
// // delimiter
// // but with quotes there is another cases
// // 


// $ cat << EOF
// line 1
// line 2
// EOF


static void heredoc_2(char *delimiter , char *r_line ,char *start) {
    char *new_l;    
    delimiter = ft_strdup(start);
    if(!delimiter)
        return ;
    new_l = strchr(delimiter , '\n');
    if(new_l)
        *new_l = '\0';
    new_l = strchr(delimiter , ' ');
    if(new_l)
        *new_l = '\0';
     while (1) {
        r_line = readline("\033[95mherdoc >$\033[0m");
        if (!r_line)
            break;

        if (strcmp(r_line, delimiter) == 0) {
            break;
        }  
        // printf("%s\n" , r_line);
    }    
}

void heredoc(char *line) {
    char *delimiter = NULL;
    char *r_line = NULL;
    char *start ;
    start =  strstr(line, "<<");
    if (!start)
        return;

    start += 2;

    while (*start == ' ')
        start++;

    // delimiter = ft_strdup(start);
    // if (!delimiter)
    //     return;

    // char *nl = strchr(delimiter, '\n');
    // if (nl) 
    //     *nl = '\0';

    // nl = strchr(delimiter, ' ');
    // if (nl) 
    //     *nl = '\0';
    heredoc_2(delimiter ,r_line , start);
    // while (1) {
    //     r_line = readline("\033[95mherdoc >$\033[0m");
    //     if (!r_line)
    //         break;

    //     if (strcmp(r_line, delimiter) == 0) {
    //         break;
    //     }

        // printf("%s\n", r_line); 
    // }

}
