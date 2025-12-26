#include "../includes/cub3d.h"

int main(int ac, char **av)
{
    t_game *game;

    if (ac != 2)
        error_exit("Usage: ./cub3D <map.cub>");
    
    game = parse_file(av[1]);
    if (!game)
        return (1);
    game->keys.w = 0;
    game->keys.a = 0;
    game->keys.s = 0;
    game->keys.d = 0;
    game->keys.left = 0;
    game->keys.right = 0;
    init_mlx(game);
    
    game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
    if (!game->win)
        error_exit("Window creation failed");
    
    game->img.img_ptr = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bits_per_pixel,
                                        &game->img.line_length, &game->img.endian);
    
    load_all_textures(game);
    init_player_camera(game);
    mlx_hook(game->win, 2, 1L<<0, key_press, game);
    mlx_hook(game->win, 3, 1L<<1, key_release, game);      // Touches clavier
    mlx_hook(game->win, 17, 0, close_game, game);        // Fermeture fenêtre (X)
    mlx_loop_hook(game->mlx, render_frame, game);        // Rendu à chaque frame
    
    mlx_loop(game->mlx);
    
    return (0);
}