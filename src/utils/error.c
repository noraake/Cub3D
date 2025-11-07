#include "../../includes/cub3d.h"

void error_exit(char *message)
{
    write(2, "Error\n", 6);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    exit(1);
}