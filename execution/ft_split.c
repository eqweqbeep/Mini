#include "exec.h"

static size_t   ft_counting(char const *s, char c) {
    size_t  i = 0, count = 0;
    while (s[i] != '\0') {
        if (s[i] != c && (i == 0 || s[i - 1] == c))
            count++;
        i++;
    }
    return count;
}

static void ft_start_end(const char *s, size_t *i, size_t *j, char c) {
    *j = 0;
    while (s[*i] && s[*i] == c)
        (*i)++;
    while (s[*i + *j] && s[*i + *j] != c)
        (*j)++;
}

static char **ft_free(char **r, size_t l) {
    while (l > 0)
        free(r[--l]);
    free(r);
    return 0;
}

char **ft_split(char const *s, char c) {
    size_t  i = 0, j, l = 0, count;
    char    **r;

    if (!s)
        return 0;
    count = ft_counting(s, c);
    r = (char **)malloc((count + 1) * sizeof(char *));
    if (!r)
        return NULL;
    while (l < count) {
        ft_start_end(s, &i, &j, c);
        r[l] = ft_substr(s, i, j);
        if (!r[l])
            return ft_free(r, l);
        i += j;
        l++;
    }
    r[count] = 0;
    return r;
}

