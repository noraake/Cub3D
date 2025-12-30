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
    
    if (game->textures.north_path)
        free(game->textures.north_path);
    if (game->textures.south_path)
        free(game->textures.south_path);
    if (game->textures.east_path)
        free(game->textures.east_path);
    if (game->textures.west_path)
        free(game->textures.west_path);
    
    free_array(game->map.grid);
    
    free(game);
}
