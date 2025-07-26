/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/25 20:46:31 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int flags(char *s)
{
    if (ft_strchr(CASES, *s))
    {
        if (*s == '|')
            return (TOKEN_PIPE);
        else if (*s == '<')
        {
            if (*(s + 1) == *s)
                return (TOKEN_HEREDOC);
            return (TOKEN_REDIRECT_IN);
        }
        else if (*s == '>')
        {
            if (*(s + 1) == *s)
                return (TOKEN_APPEND);
            return (TOKEN_REDIRECT_OUT);
        }
    }
    return (TOKEN_WORD);
}

static t_arr *re_assign_flags(t_arr **tokens)
{
    int i;

    i = 0;
    while ((*tokens)[i].token)
    {
        if ((*tokens)[i].flag == TOKEN_HEREDOC && (*tokens)[i + 1].token)
            (*tokens)[i + 1].flag = TOKEN_DELIMITER;
        else if (ft_strchr(FILE_OP, (*tokens)[i].flag) && (*tokens)[i + 1].token)
            (*tokens)[i + 1].flag = TOKEN_FILENAME;
        i++;
    }
    return (*tokens);
}

static t_arr *assign_flags(char **arr)
{
    int i;
    t_arr *tokens;

    i = 0;
    while (arr[i])
        i++;
    tokens = malloc(sizeof(t_arr) * (i + 1));
    if (!tokens)
        return (NULL);
    i = 0;
    while (arr[i])
    {
        tokens[i].token = arr[i];
        tokens[i].flag = flags(arr[i]);
        i++;
    }
    tokens[i].token = NULL;
    tokens[i].flag = 0;
    return (re_assign_flags(&tokens));
}

static void free_tokens(t_arr *tokens)
{
    int i;

    if (!tokens)
        return;
    for (i = 0; tokens[i].token; i++)
        free(tokens[i].token);
    free(tokens);
}

static void *input_analysis(char *line)
{
    char **arr;

    if (check_input(line))
    {
        fprintf(stderr, "syntax error\n");
        return (NULL);
    }
    arr = split_and_stack(line);
    if (!arr || !*arr)
    {
        fprintf(stderr, "syntax error\n");
        if (arr)
            free_tokens((t_arr *)arr);
        return (NULL);
    }
    return (assign_flags(arr));
}

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
        else if (shell->line[0])
            fprintf(stderr, "syntax error\n");
        add_history(shell->line);
        free(shell->line);
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