#include "../../includes/cub3d.h"

// void put_pixel(t_img *img, int x, int y, int color)
// {
//     char *dst;
//     if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
//         return;
//     dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
//     *(unsigned int *)dst = color;
// }

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
    draw_floor_ceiling(game);
    cast_rays(game);  
    mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
    return (0);
}