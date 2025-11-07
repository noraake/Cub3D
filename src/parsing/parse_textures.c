#include "../../includes/cub3d.h"

static char *extract_path(char *line, int start)
{
    int     i;
    int     len;
    char    *path;

    // Skip espaces après l'identifiant
    i = skip_spaces(line, start);
    
    // Calculer longueur du chemin
    len = 0;
    while (line[i + len] && line[i + len] != ' ' && 
           line[i + len] != '\t' && line[i + len] != '\n')
        len++;
    
    if (len == 0)
        return (NULL);
    
    // Extraire le chemin
    path = malloc(sizeof(char) * (len + 1));
    if (!path)
        return (NULL);
    
    len = 0;
    while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
        path[len++] = line[i++];
    path[len] = '\0';
    
    return (path);
}

int parse_north_texture(char *line, t_textures *tex)
{
    if (tex->north != NULL)
        error_exit("Duplicate NO texture");
    
    tex->north = extract_path(line, 2); // Skip "NO"
    if (!tex->north)
        error_exit("Invalid NO texture path");
    
    printf("✓ North texture: %s\n", tex->north);
    return (1);
}

int parse_south_texture(char *line, t_textures *tex)
{
    if (tex->south != NULL)
        error_exit("Duplicate SO texture");
    
    tex->south = extract_path(line, 2); // Skip "SO"
    if (!tex->south)
        error_exit("Invalid SO texture path");
    
    printf("✓ South texture: %s\n", tex->south);
    return (1);
}

int parse_west_texture(char *line, t_textures *tex)
{
    if (tex->west != NULL)
        error_exit("Duplicate WE texture");
    
    tex->west = extract_path(line, 2); // Skip "WE"
    if (!tex->west)
        error_exit("Invalid WE texture path");
    
    printf("✓ West texture: %s\n", tex->west);
    return (1);
}

int parse_east_texture(char *line, t_textures *tex)
{
    if (tex->east != NULL)
        error_exit("Duplicate EA texture");
    
    tex->east = extract_path(line, 2); // Skip "EA"
    if (!tex->east)
        error_exit("Invalid EA texture path");
    
    printf("✓ East texture: %s\n", tex->east);
    return (1);
}