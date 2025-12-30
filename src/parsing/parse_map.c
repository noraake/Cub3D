#include "../../includes/cub3d.h"

static int is_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || 
            c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static int count_map_lines(char **file, int start)
{
    int count;
    int i;
    int j;

    count = 0;
    i = start;
    while (file[i])
    {
        j = 0;
        while (file[i][j])
        {
            if (!is_map_char(file[i][j]) && file[i][j] != '\n' && 
                file[i][j] != '\t' && file[i][j] != '\r')
                return (count);
            j++;
        }
        if (count > 0 && is_empty_line(file[i]))
            error_exit("Empty line inside map");
        if (!is_empty_line(file[i]))
            count++;
        i++;
    }
    return (count);
}

static int get_map_width(char **file, int start, int height)
{
    int max_width;
    int i;
    int j;

    max_width = 0;
    i = 0;
    while (i < height)
    {
        j = 0;
        while (file[start + i][j] && file[start + i][j] != '\n' && 
               file[start + i][j] != '\r')
            j++;
        
        if (j > max_width)
            max_width = j;
        i++;
    }
    return (max_width);
}

static char *fill_line_with_spaces(char *line, int target_width)
{
    char    *new_line;
    int     i;
    int     len;

    new_line = malloc(sizeof(char) * (target_width + 1));
    if (!new_line)
        error_exit("Malloc failed");
    len = ft_strlen(line);
    i = 0;
    while (i < len && line[i] && line[i] != '\n' && line[i] != '\r' && i < target_width)
    {
        new_line[i] = line[i];
        i++;
    }
    while (i < target_width)
    {
        new_line[i] = ' ';
        i++;
    }
    new_line[i] = '\0';
    return (new_line);
}

void parse_map(t_game *game, char **file, int start)
{
    int i;
    int height;

    printf("\n=== PARSING MAP ===\n");
    height = count_map_lines(file, start);
    if (height == 0)
        error_exit("No map found");
    printf("Map height: %d\n", height);
    game->map.grid = malloc(sizeof(char *) * (height + 1));
    if (!game->map.grid)
        error_exit("Malloc failed");
    game->map.width = get_map_width(file, start, height);
    game->map.height = height;
    printf("Map width: %d\n", game->map.width);
    i = 0;
    while (i < height)
    {
        game->map.grid[i] = fill_line_with_spaces(file[start + i], game->map.width);
        i++;
    }
    game->map.grid[i] = NULL;
    printf("\nMap content:\n");
    i = 0;
    while (game->map.grid[i])
    {
        printf("[%s]\n", game->map.grid[i]);
        i++;
    }
    printf("\nMap extracted successfully!\n");
}
