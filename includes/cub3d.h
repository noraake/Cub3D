#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

/* ========== STRUCTURES ========== */

typedef struct s_map
{
    char    **grid;         // Tableau 2D de la map
    int     width;          // Largeur max
    int     height;         // Hauteur
}   t_map;

typedef struct s_player
{
    double  pos_x;          // Position X
    double  pos_y;          // Position Y
    double  dir_x;          // Direction X (-1, 0, 1)
    double  dir_y;          // Direction Y (-1, 0, 1)
    char    orientation;    // N, S, E, W
}   t_player;

typedef struct s_textures
{
    char    *north;         // Chemin texture nord
    char    *south;         // Chemin texture sud
    char    *east;          // Chemin texture est
    char    *west;          // Chemin texture ouest
    int     floor_color;    // Couleur sol (RGB encodé)
    int     ceiling_color;  // Couleur plafond (RGB encodé)
}   t_textures;

typedef struct s_game
{
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

/* ========== UTILS ========== */
void    error_exit(char *message);
char    **ft_split(char *str, char c);
int     ft_atoi(char *str);
size_t  ft_strlen(char *str);
char    *ft_strdup(char *str);
char    *ft_strtrim(char *str);
int     skip_spaces(char *str, int i);

#endif