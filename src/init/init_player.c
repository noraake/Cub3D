#include "../../includes/cub3d.h"

void init_player_camera(t_game *game)
{
    game->player.fov = M_PI / 3;
    
    if (game->player.orientation == 'N')
        game->player.angle = 3 * M_PI / 2;
    else if (game->player.orientation == 'S')
        game->player.angle = M_PI / 2;
    else if (game->player.orientation == 'E')
        game->player.angle = 0;
    else if (game->player.orientation == 'W')
        game->player.angle = M_PI;
}