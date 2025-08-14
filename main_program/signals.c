/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:14:17 by jait-chd          #+#    #+#             */
/*   Updated: 2025/08/13 06:14:37 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sigquit(int sig)
{
    (void)sig;
    write(2, "Quit (core dumped)\n", 19);
}

void sig_int(void)
{
    struct sigaction s_int;
    s_int.sa_handler = handle_sigint;
    sigemptyset(&s_int.sa_mask);
    s_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &s_int, NULL);
}

void sig_quit(void)
{
    // struct sigaction s_quit;
    // s_quit.sa_handler = handle_sigquit;
    // sigemptyset(&s_quit.sa_mask);
    // s_quit.sa_flags = SA_RESTART;
    // sigaction(SIGQUIT, &s_quit, NULL);
    signal(SIGQUIT , SIG_IGN);
}

void    sig_pipe(void)
{
    signal(SIGPIPE, SIG_IGN);
}

void signals(void)
{
    sig_int();
    sig_quit();
    sig_pipe();
}