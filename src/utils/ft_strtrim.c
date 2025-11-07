#include "../../includes/cub3d.h"

static int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

char *ft_strtrim(char *str)
{
    int     start;
    int     end;
    char    *trimmed;
    int     i;

    if (!str)
        return (NULL);
    
    // Trouver le début (skip espaces)
    start = 0;
    while (str[start] && is_space(str[start]))
        start++;
    
    // Trouver la fin (skip espaces)
    end = ft_strlen(str) - 1;
    while (end > start && is_space(str[end]))
        end--;
    
    // Allouer et copier
    trimmed = malloc(sizeof(char) * (end - start + 2));
    if (!trimmed)
        return (NULL);
    
    i = 0;
    while (start <= end)
        trimmed[i++] = str[start++];
    trimmed[i] = '\0';
    
    return (trimmed);
}