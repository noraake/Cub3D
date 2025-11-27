#include "../../includes/cub3d.h"

void init_player_camera(t_game *game)
{
    if (game->player.orientation == 'N')//↑
    {
        game->player.plane_x = 0.66;// camera plan -----> (x)
        game->player.plane_y = 0;   //(y)
    }
    else if (game->player.orientation == 'S')//↓
    {
        game->player.plane_x = -0.66; //camera plan <----- (x)
        game->player.plane_y = 0;     //(y)
    }
    else if (game->player.orientation == 'E')//->
    {
        game->player.plane_x = 0;   //(x)
        game->player.plane_y = 0.66; //camera plan ↑ (x)
    }
    else if (game->player.orientation == 'W')//<-
    {
        game->player.plane_x = 0;    //(x)
        game->player.plane_y = -0.66;//camera plan ↓ (y)
    }
}