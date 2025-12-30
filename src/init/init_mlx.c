#include "../../includes/cub3d.h"

void init_mlx(t_game *game)
{
    printf("\n=== INITIALIZING MLX ===\n");
    
    game->mlx = mlx_init();
    if (!game->mlx)
        error_exit("MLX initialization failed");
    printf("MLX initialized successfully!\n");
}