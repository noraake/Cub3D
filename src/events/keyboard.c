#include "../../includes/cub3d.h"

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

static void move_forward(t_game *game)
{
    double new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
    double new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
    
    if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
        game->player.pos_x = new_x;
    if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
        game->player.pos_y = new_y;
}

static void move_backward(t_game *game)
{
    double new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
    double new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
    
    if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
        game->player.pos_x = new_x;
    if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
        game->player.pos_y = new_y;
}

static void strafe_left(t_game *game)
{
    double new_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED;
    double new_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED;
    
    if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
        game->player.pos_x = new_x;
    if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
        game->player.pos_y = new_y;
}

static void strafe_right(t_game *game)
{
    double new_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED;
    double new_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED;
    
    if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
        game->player.pos_x = new_x;
    if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
        game->player.pos_y = new_y;
}

static void rotate_left(t_game *game)
{
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;
    
    game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - 
                         game->player.dir_y * sin(ROT_SPEED);
    game->player.dir_y = old_dir_x * sin(ROT_SPEED) + 
                         game->player.dir_y * cos(ROT_SPEED);
    game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - 
                           game->player.plane_y * sin(ROT_SPEED);
    game->player.plane_y = old_plane_x * sin(ROT_SPEED) + 
                           game->player.plane_y * cos(ROT_SPEED);
}

static void rotate_right(t_game *game)
{
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;
    
    game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - 
                         game->player.dir_y * sin(-ROT_SPEED);
    game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + 
                         game->player.dir_y * cos(-ROT_SPEED);
    game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - 
                           game->player.plane_y * sin(-ROT_SPEED);
    game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + 
                           game->player.plane_y * cos(-ROT_SPEED);
}

int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        close_game(game);
    else if (keycode == KEY_W)
        move_forward(game);
    else if (keycode == KEY_S)
        move_backward(game);
    else if (keycode == KEY_A)
        strafe_left(game);
    else if (keycode == KEY_D)
        strafe_right(game);
    else if (keycode == KEY_LEFT)
        rotate_left(game);
    else if (keycode == KEY_RIGHT)
        rotate_right(game);
    
    return (0);
}

int close_game(t_game *game)
{
    free_textures(game);
    if (game->img.img_ptr)
        mlx_destroy_image(game->mlx, game->img.img_ptr);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    free_game(game);
    exit(0);
}