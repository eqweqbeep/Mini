
#include "minishell.h"
#include <stdbool.h>

//1st of all we need a prompt 
// so we create a funtion that generate a prompt with readline function and keep it in a true while till 
// till we stop with siganl or exi ..
/*
void create_prompt(t_shell *shell) {
	while((shell->line = readline("CrounShell >$")) != NULL) {
		if(shell->line)
			add_history(shell->line);		
	}
}
*/
//hi my dear friend this our new minishell 
// lets slice this into parts and make an open strructers that we can control from now on 
// and i would like to create  3 directorys one for main_progarm and the other tow is for parsing and execution 
// so when you fork this project work only on you parsing directory 
// that it must you do a header file that contain a structers which means  A nested struct (or structure within a structure)
int main(int counter , char **vectors , char **env) {
	t_shell *shell = malloc(sizeof(t_shell));
	if(!shell)
		return 1;
	while(true) {
	//create_prompt(shell);
	shell->line = readline("CrounsPrompt > ");
	if(!shell->line) 
		return -1;	
	//execution(shell->line , env);	
	piping(shell->line ,env);
	//sleep(900);
	// here iam creating a function that check if the cmd is built in
	//is_built_in(shell->line , env);
	if(shell->line)
		add_history(shell->line);
	}
}
