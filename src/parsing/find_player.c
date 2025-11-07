#include "../../includes/cub3d.h"

static int is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void set_player_direction(t_player *player, char orientation)
{
    player->orientation = orientation;
    
    if (orientation == 'N')
    {
        player->dir_x = 0;
        player->dir_y = -1;
    }
    else if (orientation == 'S')
    {
        player->dir_x = 0;
        player->dir_y = 1;
    }
    else if (orientation == 'E')
    {
        player->dir_x = 1;
        player->dir_y = 0;
    }
    else if (orientation == 'W')
    {
        player->dir_x = -1;
        player->dir_y = 0;
    }
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
    
    printf("Player position: (%.1f, %.1f)\n", 
           game->player.pos_x, game->player.pos_y);
    printf("Player direction: (%.1f, %.1f)\n", 
           game->player.dir_x, game->player.dir_y);
    
    printf("✅ Player initialized!\n");
}
