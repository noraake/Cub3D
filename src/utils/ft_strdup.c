#include "../../includes/cub3d.h"

char *ft_strdup(char *str)
{
    char    *new;
    int     i;

    if (!str)
        return (NULL);
    new = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!new)
        return (NULL);
    i = 0;
    while (str[i])
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}