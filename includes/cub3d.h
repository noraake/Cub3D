#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"  // Ajouter MinilibX

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
    t_map       map;
    t_player    player;
    t_textures  textures;
}   t_game;

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

#endif