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

int main(int ac, char **av)
{
    t_game *game;

    if (ac != 2)
        error_exit("Usage: ./cub3D <map.cub>");
    
    game = parse_file(av[1]);
    if (!game)
        return (1);
    
    printf("\n========================================\n");
    printf("✅ PARSING SUCCESSFUL!\n");
    printf("========================================\n");
    printf("North texture: %s\n", game->textures.north);
    printf("South texture: %s\n", game->textures.south);
    printf("West texture: %s\n", game->textures.west);
    printf("East texture: %s\n", game->textures.east);
    printf("Floor color: RGB(%d,%d,%d)\n",
           (game->textures.floor_color >> 16) & 0xFF,
           (game->textures.floor_color >> 8) & 0xFF,
           game->textures.floor_color & 0xFF);
    printf("Ceiling color: RGB(%d,%d,%d)\n",
           (game->textures.ceiling_color >> 16) & 0xFF,
           (game->textures.ceiling_color >> 8) & 0xFF,
           game->textures.ceiling_color & 0xFF);
    
    print_map(game);
    
    free_game(game);
    return (0);
}