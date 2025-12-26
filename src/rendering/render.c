#include "../../includes/cub3d.h"

static void draw_floor_ceiling(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < SCREEN_HEIGHT / 2)
    {
        x = 0;
        while (x < SCREEN_WIDTH)
        {
            put_pixel(&game->img, x, y, game->textures.ceiling_color);
            x++;
        }
        y++;
    }
    while (y < SCREEN_HEIGHT)
    {
        x = 0;
        while (x < SCREEN_WIDTH)
        {
            put_pixel(&game->img, x, y, game->textures.floor_color);
            x++;
        }
        y++;
    }
}

int render_frame(t_game *game)
{
    handle_movement(game);
    draw_floor_ceiling(game);
    cast_rays(game);  
    mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
    return (0);
}