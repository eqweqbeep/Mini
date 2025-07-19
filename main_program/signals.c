#include "minishell.h"


void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    // if(sig == SIGINT)
        // exit(130);
    // else if(sig == SIGQUIT)
        // exit(131);
}
// here on signal part there is somethings dosent handled 
// like Try ctrl-C after running a blocking command like cat without arguments or grep “something“.
// also there is another case when ...
void setup_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN); 
} 