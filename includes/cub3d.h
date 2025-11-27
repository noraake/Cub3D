#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"  // Ajouter MinilibX

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03

/* ========== STRUCTURES ========== */

typedef struct s_img
{
    void    *img_ptr;       // Pointeur vers l'image MLX
    char    *addr;          // Adresse des données de l'image
    int     width;          // Largeur de l'image
    int     height;         // Hauteur de l'image
    int     bits_per_pixel; // Bits par pixel
    int     line_length;    // Longueur d'une ligne
    int     endian;         // Endianness
}   t_img;

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
}   t_map;

typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
    char    orientation;
}   t_player;

typedef struct s_textures
{
    char    *north_path;     // Renommer pour clarifier
    char    *south_path;
    char    *east_path;
    char    *west_path;
    t_img   north_img;       // Ajouter les images
    t_img   south_img;
    t_img   east_img;
    t_img   west_img;
    int     floor_color;
    int     ceiling_color;
}   t_textures;

typedef struct s_game
{
    void        *mlx;        // Ajouter le pointeur MLX
    void        *win;
    t_img       img;
    t_map       map;
    t_player    player;
    t_textures  textures;
}   t_game;

typedef struct s_ray
{
    double  camera_x;      // Position x dans l'espace caméra
    double  ray_dir_x;     // Direction x du rayon
    double  ray_dir_y;     // Direction y du rayon
    int     map_x;         // Position x sur la map
    int     map_y;         // Position y sur la map
    double  side_dist_x;   // Distance au prochain côté x
    double  side_dist_y;   // Distance au prochain côté y
    double  delta_dist_x;  // Distance entre chaque x
    double  delta_dist_y;  // Distance entre chaque y
    int     step_x;        // Direction du step (-1 ou 1)
    int     step_y;        // Direction du step (-1 ou 1)
    int     hit;           // Mur touché ?
    int     side;          // Côté touché (NS=0, EW=1)
    double  perp_wall_dist; // Distance perpendiculaire au mur
    int     line_height;   // Hauteur de la ligne à dessiner
    int     draw_start;    // Début du dessin
    int     draw_end;      // Fin du dessin
}   t_ray;

/* ========== PARSING ========== */

t_game  *parse_file(char *filename);
void    free_game(t_game *game);
char    **read_file(char *filename);
int     parse_north_texture(char *line, t_textures *tex);
int     parse_south_texture(char *line, t_textures *tex);
int     parse_west_texture(char *line, t_textures *tex);
int     parse_east_texture(char *line, t_textures *tex);
int     parse_floor_color(char *line, t_textures *tex);
int     parse_ceiling_color(char *line, t_textures *tex);
void    parse_map(t_game *game, char **file, int start);
int     is_empty_line(char *line);
void    find_player(t_game *game);
void    validate_map(t_game *game);

/* ========== TEXTURES ========== */
void    load_all_textures(t_game *game);
int     get_texture_pixel(t_img *img, int x, int y);
void    free_textures(t_game *game);

/* ========== INIT ========== */
void    init_mlx(t_game *game);

/* ========== UTILS ========== */
void    error_exit(char *message);
char    **ft_split(char *str, char c);
int     ft_atoi(char *str);
size_t  ft_strlen(char *str);
char    *ft_strdup(char *str);
char    *ft_strtrim(char *str);
int     skip_spaces(char *str, int i);
int     is_empty_line(char *line);

/* ========== RENDERING ========== */
void    put_pixel(t_img *img, int x, int y, int color);
int     render_frame(t_game *game);
void    draw_vertical_line(t_game *game, t_ray *ray, int x);

/* ========== RAYCASTING ========== */
void    cast_rays(t_game *game);

/* ========== EVENTS ========== */
int     key_press(int keycode, t_game *game);
int     close_game(t_game *game);

/* ========== PLAYER ========== */
void    init_player_camera(t_game *game);
/* ========== keyboard ========== */
int key_press(int keycode, t_game *game);
int close_game(t_game *game);

#endif