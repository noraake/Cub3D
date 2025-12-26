#include "../../includes/cub3d.h"

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_LEFT 65363
#define KEY_RIGHT 65361
#define KEY_ESC 65307


static int is_walkable(t_game *game, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;

    if (map_x < 0 || map_x >= game->map.width ||
        map_y < 0 || map_y >= game->map.height)
        return (0);

    if (game->map.grid[map_y][map_x] == '1' ||
        game->map.grid[map_y][map_x] == ' ')
        return (0);

    return (1);
}

// ===== Déplacements =====
static void move_forward(t_game *game)
{
    double new_x = game->player.pos_x + cos(game->player.angle) * MOVE_SPEED;
    double new_y = game->player.pos_y + sin(game->player.angle) * MOVE_SPEED;

    if (is_walkable(game, new_x, new_y))
    {
        game->player.pos_x = new_x;
        game->player.pos_y = new_y;
    }
}

static void move_backward(t_game *game)
{
    double new_x = game->player.pos_x - cos(game->player.angle) * MOVE_SPEED;
    double new_y = game->player.pos_y - sin(game->player.angle) * MOVE_SPEED;

    if (game->map.grid[(int)new_y][(int)new_x] != '1')
    {
        game->player.pos_x = new_x;
        game->player.pos_y = new_y;
    }
}

static void strafe_left(t_game *game)
{
    // Perpendiculaire = angle - 90°
    double strafe_angle = game->player.angle - M_PI / 2;
    double new_x = game->player.pos_x + cos(strafe_angle) * MOVE_SPEED;
    double new_y = game->player.pos_y + sin(strafe_angle) * MOVE_SPEED;

    if (game->map.grid[(int)new_y][(int)new_x] != '1')
    {
        game->player.pos_x = new_x;
        game->player.pos_y = new_y;
    }
}

static void strafe_right(t_game *game)
{
    double strafe_angle = game->player.angle + M_PI / 2;
    double new_x = game->player.pos_x + cos(strafe_angle) * MOVE_SPEED;
    double new_y = game->player.pos_y + sin(strafe_angle) * MOVE_SPEED;

    if (game->map.grid[(int)new_y][(int)new_x] != '1')
    {
        game->player.pos_x = new_x;
        game->player.pos_y = new_y;
    }
}

// ===== Rotation =====
static void rotate_player(t_game *game, double rot_speed)
{
    game->player.angle += rot_speed;
    if (game->player.angle < 0)
        game->player.angle += 2 * M_PI;
    if (game->player.angle >= 2 * M_PI)
        game->player.angle -= 2 * M_PI;
}

// ===== Hooks =====
int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_W) game->keys.w = 1;
    if (keycode == KEY_S) game->keys.s = 1;
    if (keycode == KEY_A) game->keys.a = 1;
    if (keycode == KEY_D) game->keys.d = 1;
    if (keycode == KEY_LEFT) game->keys.left = 1;
    if (keycode == KEY_RIGHT) game->keys.right = 1;
    if (keycode == KEY_ESC) close_game(game);
    return (0);
}

int key_release(int keycode, t_game *game)
{
    if (keycode == KEY_W) game->keys.w = 0;
    if (keycode == KEY_S) game->keys.s = 0;
    if (keycode == KEY_A) game->keys.a = 0;
    if (keycode == KEY_D) game->keys.d = 0;
    if (keycode == KEY_LEFT) game->keys.left = 0;
    if (keycode == KEY_RIGHT) game->keys.right = 0;
    return (0);
}

// ===== Appliquer mouvement =====
void handle_movement(t_game *game)
{
    if (game->keys.w) move_forward(game);
    if (game->keys.s) move_backward(game);
    if (game->keys.a) strafe_left(game);
    if (game->keys.d) strafe_right(game);
    if (game->keys.left) rotate_player(game, ROT_SPEED);
    if (game->keys.right) rotate_player(game, -ROT_SPEED);
}

// ===== Fermer jeu =====
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