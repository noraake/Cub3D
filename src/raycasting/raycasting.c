#include "../../includes/cub3d.h"

static void init_ray(t_ray *ray, t_game *game, int x)
{
    double ray_angle;
    ray_angle = game->player.angle - (game->player.fov / 2) + 
                (x * game->player.fov / SCREEN_WIDTH);
    ray->ray_dir_x = cos(ray_angle);
    ray->ray_dir_y = sin(ray_angle);
    ray->map_x = (int)game->player.pos_x;
    ray->map_y = (int)game->player.pos_y;
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    ray->hit = 0;
}

static void calculate_step(t_ray *ray, t_game *game)
{
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
    }
    
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
    }
}

static void perform_dda(t_ray *ray, t_game *game)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (ray->map_x < 0 || ray->map_x >= game->map.width ||
            ray->map_y < 0 || ray->map_y >= game->map.height)
        {
            ray->hit = 1;
            break;
        }
        
        if (game->map.grid[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

static void calculate_wall_height(t_ray *ray, t_game *game)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - game->player.pos_x + 
                               (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - game->player.pos_y + 
                               (1 - ray->step_y) / 2) / ray->ray_dir_y;
    
    ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
    ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
    
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    
    ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
    
    if (ray->draw_end >= SCREEN_HEIGHT)
        ray->draw_end = SCREEN_HEIGHT - 1;
}

void cast_rays(t_game *game)
{
    t_ray   ray;
    int     x;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        init_ray(&ray, game, x);
        calculate_step(&ray, game);
        perform_dda(&ray, game);
        calculate_wall_height(&ray, game);
        draw_vertical_line(game, &ray, x);
        x++;
    }
}