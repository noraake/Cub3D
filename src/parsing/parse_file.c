#include "../../includes/cub3d.h"

static void init_game(t_game *game)
{
    game->textures.north_path = NULL;
    game->textures.south_path = NULL;
    game->textures.east_path = NULL;
    game->textures.east_path = NULL;
    game->textures.floor_color = -1;
    game->textures.ceiling_color = -1;
    game->map.grid = NULL;
    game->map.width = 0;
    game->map.height = 0;
    game->player.pos_x = 0;
    game->player.pos_y = 0;
}

static int parse_element(char *line, t_game *game)
{
    char *trimmed;
    int result;

    trimmed = ft_strtrim(line);
    if (!trimmed || is_empty_line(trimmed))
    {
        if (trimmed)
            free(trimmed);
        return (0); // Ligne vide, skip
    }
    
    result = 0;
    // Ajouter plus d'espaces possibles après l'identifiant
    if (trimmed[0] == 'N' && trimmed[1] == 'O' && (trimmed[2] == ' ' || trimmed[2] == '\t'))
        result = parse_north_texture(trimmed, &game->textures);
    else if (trimmed[0] == 'S' && trimmed[1] == 'O' && (trimmed[2] == ' ' || trimmed[2] == '\t'))
        result = parse_south_texture(trimmed, &game->textures);
    else if (trimmed[0] == 'W' && trimmed[1] == 'E' && (trimmed[2] == ' ' || trimmed[2] == '\t'))
        result = parse_west_texture(trimmed, &game->textures);
    else if (trimmed[0] == 'E' && trimmed[1] == 'A' && (trimmed[2] == ' ' || trimmed[2] == '\t'))
        result = parse_east_texture(trimmed, &game->textures);
    else if (trimmed[0] == 'F' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
        result = parse_floor_color(trimmed, &game->textures);
    else if (trimmed[0] == 'C' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
        result = parse_ceiling_color(trimmed, &game->textures);
    
    free(trimmed);
    return (result);
}

static void check_all_elements(t_game *game)
{
    if (!game->textures.north_path)
        error_exit("Missing NO (north) texture");
    if (!game->textures.south_path)
        error_exit("Missing SO (south) texture");
    if (!game->textures.west_path)
        error_exit("Missing WE (west) texture");
    if (!game->textures.east_path)
        error_exit("Missing EA (east) texture");
    if (game->textures.floor_color == -1)
        error_exit("Missing F (floor) color");
    if (game->textures.ceiling_color == -1)
        error_exit("Missing C (ceiling) color");
}

t_game *parse_file(char *filename)
{
    t_game  *game;
    char    **file_content;
    int     i;
    int     elements_count;

    // Vérifier extension .cub
    if (ft_strlen(filename) < 4 || 
        strcmp(filename + ft_strlen(filename) - 4, ".cub") != 0)
        error_exit("File must have .cub extension");
    
    // Lire tout le fichier
    file_content = read_file(filename);
    
    // Initialiser la structure
    game = malloc(sizeof(t_game));
    if (!game)
        error_exit("Malloc failed");
    init_game(game);
    
    // Parser les éléments (textures et couleurs)
    printf("\n=== PARSING ELEMENTS ===\n");
    i = 0;
    elements_count = 0;
    while (file_content[i] && elements_count < 6) // On attend 6 éléments (4 textures + 2 couleurs)
    {
        if (parse_element(file_content[i], game))
        {
            elements_count++;
        }
        i++;
    }
    
    // Vérifier que tous les éléments sont présents
    check_all_elements(game);
    
    // Trouver où commence la map (première ligne non-vide après les éléments)
    while (file_content[i] && is_empty_line(file_content[i]))
        i++;
    
    if (!file_content[i])
        error_exit("No map found in file");
    
    printf("\n=== MAP STARTS AT LINE %d ===\n", i);
    
    // Parser la map
    parse_map(game, file_content, i);

    // Trouver et initialiser le joueur
    find_player(game);

    // Valider que la map est fermée
    validate_map(game);
    
    printf("\n✅ All elements parsed successfully!\n\n");

    // Free file_content (on en a plus besoin)
    i = 0;
    while (file_content[i])
    {
        free(file_content[i]);
        i++;
    }
    free(file_content);
    
    return (game);
}
