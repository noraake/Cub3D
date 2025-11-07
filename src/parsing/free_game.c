#include "../../includes/cub3d.h"

static void free_array(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void free_game(t_game *game)
{
    if (!game)
        return;
    
    if (game->textures.north)
        free(game->textures.north);
    if (game->textures.south)
        free(game->textures.south);
    if (game->textures.east)
        free(game->textures.east);
    if (game->textures.west)
        free(game->textures.west);
    
    free_array(game->map.grid);
    
    free(game);
}