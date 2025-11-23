#include "../includes/cub3d.h"

static void print_map(t_game *game)
{
    int i;

    printf("\n=== FINAL MAP ===\n");
    printf("Size: %d x %d\n", game->map.width, game->map.height);
    i = 0;
    while (i < game->map.height)
    {
        printf("%s\n", game->map.grid[i]);
        i++;
    }
}

static void print_player_info(t_game *game)
{
    printf("\n=== PLAYER INFO ===\n");
    printf("Position: (%.2f, %.2f)\n", 
           game->player.pos_x, game->player.pos_y);
    printf("Orientation: %c\n", game->player.orientation);
    printf("Direction vector: (%.1f, %.1f)\n", 
           game->player.dir_x, game->player.dir_y);
}

int main(int ac, char **av)
{
    t_game *game;

    if (ac != 2)
        error_exit("Usage: ./cub3D <map.cub>");
    
    // Parser le fichier
    game = parse_file(av[1]);
    if (!game)
        return (1);
    
    // Initialiser MLX
    init_mlx(game);
    
    // Charger les textures
    load_all_textures(game);
    
    printf("\n========================================\n");
    printf("✅ EVERYTHING LOADED SUCCESSFULLY!\n");
    printf("========================================\n");
    printf("\n=== TEXTURES ===\n");
    printf("North: %s (%dx%d)\n", game->textures.north_path,
           game->textures.north_img.width, game->textures.north_img.height);
    printf("South: %s (%dx%d)\n", game->textures.south_path,
           game->textures.south_img.width, game->textures.south_img.height);
    printf("West:  %s (%dx%d)\n", game->textures.west_path,
           game->textures.west_img.width, game->textures.west_img.height);
    printf("East:  %s (%dx%d)\n", game->textures.east_path,
           game->textures.east_img.width, game->textures.east_img.height);
    
    printf("\n=== COLORS ===\n");
    printf("Floor:   RGB(%d, %d, %d)\n",
           (game->textures.floor_color >> 16) & 0xFF,
           (game->textures.floor_color >> 8) & 0xFF,
           game->textures.floor_color & 0xFF);
    printf("Ceiling: RGB(%d, %d, %d)\n",
           (game->textures.ceiling_color >> 16) & 0xFF,
           (game->textures.ceiling_color >> 8) & 0xFF,
           game->textures.ceiling_color & 0xFF);
    
    print_player_info(game);
    print_map(game);
    
    printf("\n========================================\n");
    
    // Libérer tout
    free_textures(game);
    free_game(game);
    
    return (0);
}