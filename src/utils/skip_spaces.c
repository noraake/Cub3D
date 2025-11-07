#include "../../includes/cub3d.h"

int skip_spaces(char *str, int i)
{
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    return (i);
}