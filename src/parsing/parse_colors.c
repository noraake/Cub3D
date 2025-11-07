#include "../../includes/cub3d.h"

static int ft_atoi_color(char *str)
{
    int result;
    int i;

    result = 0;
    i = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result);
}

static int create_rgb(int r, int g, int b)
{
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        error_exit("RGB values must be between 0 and 255");
    
    return ((r << 16) | (g << 8) | b);
}

static int parse_rgb(char *line, int start)
{
    int r;
    int g;
    int b;
    int i;

    i = skip_spaces(line, start);
    
    // Parser R
    r = ft_atoi_color(&line[i]);
    while (line[i] >= '0' && line[i] <= '9')
        i++;
    
    // Vérifier virgule
    if (line[i] != ',')
        error_exit("Invalid RGB format (missing comma after R)");
    i++;
    
    // Parser G
    g = ft_atoi_color(&line[i]);
    while (line[i] >= '0' && line[i] <= '9')
        i++;
    
    // Vérifier virgule
    if (line[i] != ',')
        error_exit("Invalid RGB format (missing comma after G)");
    i++;
    
    // Parser B
    b = ft_atoi_color(&line[i]);
    
    return (create_rgb(r, g, b));
}

int parse_floor_color(char *line, t_textures *tex)
{
    if (tex->floor_color != -1)
        error_exit("Duplicate F (floor) color");
    
    tex->floor_color = parse_rgb(line, 1); // Skip "F"
    
    printf("✓ Floor color: %d (RGB: %d,%d,%d)\n", 
           tex->floor_color,
           (tex->floor_color >> 16) & 0xFF,
           (tex->floor_color >> 8) & 0xFF,
           tex->floor_color & 0xFF);
    return (1);
}

int parse_ceiling_color(char *line, t_textures *tex)
{
    if (tex->ceiling_color != -1)
        error_exit("Duplicate C (ceiling) color");
    
    tex->ceiling_color = parse_rgb(line, 1); // Skip "C"
    
    printf("✓ Ceiling color: %d (RGB: %d,%d,%d)\n", 
           tex->ceiling_color,
           (tex->ceiling_color >> 16) & 0xFF,
           (tex->ceiling_color >> 8) & 0xFF,
           tex->ceiling_color & 0xFF);
    return (1);
}