/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/26 09:01:13 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_prompt(t_shell *shell)
{
    t_arr *arr;

    while (1)
    {
        setup_signals();
        shell->line = readline("\033[95mCrounShell >$\033[0m");
        if (shell->line == NULL)
        {
            write(1, "exit\n", 5);
            free(shell);
            exit(0);
        }
        if (!check_input(shell->line))
        {
            arr = input_analysis(shell->line);
            if (arr)
            {
                execution(arr, shell->env);
                free_tokens(arr);
            }
        }
        add_history(shell->line);
    }
}

int main(int c, char **v, char **env)
{
    t_shell *shell;

    (void)c;
    (void)v;
    shell = malloc(sizeof(t_shell));
    if (!shell)
        return (1);
    shell->env = env;
    create_prompt(shell);
    free(shell);
    return (0);
}