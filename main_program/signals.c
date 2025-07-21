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

void handle_sigquit(int sig) {
    (void)sig;
}

void sig_int(void) {
    struct sigaction s_int;
    s_int.sa_handler = handle_sigint;
    sigemptyset(&s_int.sa_mask);
    s_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &s_int, NULL);
}

void sig_quit(void) {
    // struct sigaction s_quite;
    // s_quite.sa_handler = handle_sigquit;
    // s_quite.sa_flags = SA_RESTART;
    // sigaction(SIGQUIT , &s_quite , NULL);
    signal(SIGQUIT, SIG_IGN); 
}
// here on signal part there is somethings dosent handled 
// like Try ctrl-C after running a blocking command like cat without arguments or grep “something“.
// also there is another case when ...
void setup_signals(void)
{
    sig_int();
    sig_quit();
} 