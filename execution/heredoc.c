#include "exec.h"

// the base of herdoc is [n] << [-]Word
//              here_document
// delimiter
// but with quotes there is another cases
// 
void heredoc(char *line) {
    char *r_line;
    char **the_whole = ft_split(r_line , ' ');
    // int i = 0;
    if(ft_strncmp(line , "<<" , 2) == 0) {
        while(1) {
            r_line = readline("Herdoc > ");       
            if(the_whole[0] != the_whole[1])
                exit(1);
            //       printf("%s\n" , r_line);         
        }
    }
}