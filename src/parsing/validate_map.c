#include "../../includes/cub3d.h"

static int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == ' ');
}

static void check_valid_characters(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if (!is_valid_map_char(game->map.grid[y][x]))
                error_exit("Invalid character in map (only 0, 1, space allowed after player extraction)");
            x++;
        }
        y++;
    }
}

static char **copy_map(t_game *game)
{
    char    **copy;
    int     i;

    copy = malloc(sizeof(char *) * (game->map.height + 1));
    if (!copy)
        error_exit("Malloc failed");
    
    i = 0;
    while (i < game->map.height)
    {
        copy[i] = ft_strdup(game->map.grid[i]);
        if (!copy[i])
            error_exit("Malloc failed");
        i++;
    }
    copy[i] = NULL;
    
    return (copy);
}

static void free_map_copy(char **map, int height)
{
    int i;

    i = 0;
    while (i < height)
    {
        free(map[i]);
        i++;
    }
    free(map);
}

static void flood_fill(char **map, int x, int y, int width, int height)
{
    // Si hors limites, c'est une erreur (map ouverte)
    if (x < 0 || x >= width || y < 0 || y >= height)
        error_exit("Map is not closed (player can escape)");
    
    // Si c'est un mur, on s'arrête
    if (map[y][x] == '1')
        return;
    
    // Si c'est un espace en bordure ou hors map, erreur
    if (map[y][x] == ' ')
        error_exit("Map is not closed (space found in path)");
    
    // Si déjà visité, on s'arrête
    if (map[y][x] == 'V')
        return;
    
    // Marquer comme visité
    map[y][x] = 'V';
    
    // Remplir récursivement dans les 4 directions
    flood_fill(map, x + 1, y, width, height);
    flood_fill(map, x - 1, y, width, height);
    flood_fill(map, x, y + 1, width, height);
    flood_fill(map, x, y - 1, width, height);
}

static void check_borders(t_game *game)
{
    int x;
    int y;

    // Vérifier première et dernière ligne
    y = 0;
    while (y < game->map.height)
    {
        if (y == 0 || y == game->map.height - 1)
        {
            x = 0;
            while (x < game->map.width)
            {
                if (game->map.grid[y][x] == '0')
                    error_exit("Map not closed: empty space on border");
                x++;
            }
        }
        y++;
    }
    
    // Vérifier première et dernière colonne
    x = 0;
    while (x < game->map.width)
    {
        if (x == 0 || x == game->map.width - 1)
        {
            y = 0;
            while (y < game->map.height)
            {
                if (game->map.grid[y][x] == '0')
                    error_exit("Map not closed: empty space on border");
                y++;
            }
        }
        x++;
    }
}

void validate_map(t_game *game)
{
    char    **map_copy;
    int     start_x;
    int     start_y;

    printf("\n=== VALIDATING MAP ===\n");
    
    // Vérifier que tous les caractères sont valides
    check_valid_characters(game);
    printf("✓ All characters valid\n");
    
    // Vérifier les bordures
    check_borders(game);
    printf("✓ Borders checked\n");
    
    // Copier la map pour le flood fill
    map_copy = copy_map(game);
    
    // Position de départ du flood fill (position du joueur)
    start_x = (int)game->player.pos_x;
    start_y = (int)game->player.pos_y;
    
    printf("Starting flood fill from (%d, %d)\n", start_x, start_y);
    
    // Lancer le flood fill
    flood_fill(map_copy, start_x, start_y, game->map.width, game->map.height);
    
    // Libérer la copie
    free_map_copy(map_copy, game->map.height);
    
    printf("✓ Map is closed (flood fill successful)\n");
    printf("✅ Map validation complete!\n");
}