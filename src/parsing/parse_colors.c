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

static int check_digit_sequence(char *line, int *i)
{
    int start;
    int value;

    start = *i;
    if (line[*i] < '0' || line[*i] > '9')
        error_exit("Invalid RGB format: expected digit");
    while (line[*i] >= '0' && line[*i] <= '9')
        (*i)++;
    value = ft_atoi_color(&line[start]);
    return (value);
}

static void check_comma(char *line, int *i)
{
    if (line[*i] != ',')
        error_exit("Invalid RGB format: expected comma");
    (*i)++;
    if (line[*i] == ',')
        error_exit("Invalid RGB format: multiple commas");
    while (line[*i] == ' ' || line[*i] == '\t')
        (*i)++;
}

static void check_end_of_rgb(char *line, int i)
{
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r')
            error_exit("Invalid RGB format: unexpected characters after RGB values");
        i++;
    }
}

static int parse_rgb(char *line, int start)
{
    int r;
    int g;
    int b;
    int i;

    i = skip_spaces(line, start);
    r = check_digit_sequence(line, &i);
    check_comma(line, &i);
    g = check_digit_sequence(line, &i);
    check_comma(line, &i);
    b = check_digit_sequence(line, &i);
    check_end_of_rgb(line, i);
    return (create_rgb(r, g, b));
}

int parse_floor_color(char *line, t_textures *tex)
{
    if (tex->floor_color != -1)
        error_exit("Duplicate F (floor) color");
    
    tex->floor_color = parse_rgb(line, 1);
    
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
    
    tex->ceiling_color = parse_rgb(line, 1);
    
    printf("✓ Ceiling color: %d (RGB: %d,%d,%d)\n", 
           tex->ceiling_color,
           (tex->ceiling_color >> 16) & 0xFF,
           (tex->ceiling_color >> 8) & 0xFF,
           tex->ceiling_color & 0xFF);
    return (1);
}