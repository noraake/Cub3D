#include "../../includes/cub3d.h"

int is_empty_line(char *line)
{
    int i;

    if (!line)
        return (1);
    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && 
            line[i] != '\n' && line[i] != '\r')
            return (0);
        i++;
    }
    return (1);
}