#include "../../includes/cub3d.h"

static t_img *select_texture(t_game *game, t_ray *ray)
{
    if (ray->side == 0)
    {
        if (ray->ray_dir_x > 0)
            return (&game->textures.east_img);
        else
            return (&game->textures.west_img);
    }
    else
    {
        if (ray->ray_dir_y > 0)
            return (&game->textures.south_img);
        else
            return (&game->textures.north_img);
    }
}

static double calculate_wall_x(t_game *game, t_ray *ray)
{
    double wall_x;
    
    if (ray->side == 0)
        wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    wall_x -= floor(wall_x);
    return (wall_x);
}

void    draw_vertical_line(t_game *game, t_ray *ray, int x)
{
    t_img   *texture;
    double  wall_x;
    int     tex_x;
    double  step;
    double  tex_pos;
    int     y;
    int     tex_y;
    int     color;

    texture = select_texture(game, ray);
    wall_x = calculate_wall_x(game, ray);
    tex_x = (int)(wall_x * (double)texture->width);
    if ((ray->side == 0 && ray->ray_dir_x > 0) || 
        (ray->side == 1 && ray->ray_dir_y < 0))
        tex_x = texture->width - tex_x - 1;
    
    step = 1.0 * texture->height / ray->line_height;
    tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
    
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        tex_y = (int)tex_pos & (texture->height - 1);
        tex_pos += step;
        color = get_texture_pixel(texture, tex_x, tex_y);
        if (ray->side == 1)
            color = (color >> 1) & 8355711; // Assombrir les murs EW
        put_pixel(&game->img, x, y, color);
        y++;
    }
}

void    put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}