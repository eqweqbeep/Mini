#include "minishell.h"

int flags(char *s)
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

t_arr *re_assign_flags(t_arr **tokens)
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

t_arr *assign_flags(char **arr)
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

void free_tokens(t_arr *tokens)
{
    int i;

    if (!tokens)
        return;
    for (i = 0; tokens[i].token; i++)
        free(tokens[i].token);
    free(tokens);
}

void *input_analysis(char *line)
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
