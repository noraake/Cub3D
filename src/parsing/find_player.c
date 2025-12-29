#include "../../includes/cub3d.h"

static int is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void set_player_direction(t_player *player, char orientation)
{
    player->orientation = orientation;

    if (orientation == 'N')
        player->angle = -M_PI / 2;
    else if (orientation == 'S')
        player->angle = M_PI / 2;
    else if (orientation == 'E')
        player->angle = 0;
    else if (orientation == 'W')
        player->angle = M_PI;

    player->dir_x = cos(player->angle);
    player->dir_y = sin(player->angle);
}

void find_player(t_game *game)
{
    int     x;
    int     y;
    int     player_count;

    printf("\n=== FINDING PLAYER ===\n");
    
    player_count = 0;
    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if (is_player_char(game->map.grid[y][x]))
            {
                player_count++;
                if (player_count > 1)
                    error_exit("Multiple players found in map");
                
                // Position du joueur (centre de la case)
                game->player.pos_x = x + 0.5;
                game->player.pos_y = y + 0.5;
                
                // Direction selon l'orientation
                set_player_direction(&game->player, game->map.grid[y][x]);
                
                printf("Player found at (%d, %d) facing %c\n", 
                       x, y, game->map.grid[y][x]);
                
                // Remplacer par '0' dans la map
                game->map.grid[y][x] = '0';
            }
            x++;
        }
        y++;
    }
    
    if (player_count == 0)
        error_exit("No player found in map");
    
    printf("✅ Player initialized!\n");
}
