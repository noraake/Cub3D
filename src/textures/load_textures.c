#include "../../includes/cub3d.h"

static t_img load_texture(void *mlx, char *path)
{
    t_img img;

    printf("Loading texture: %s\n", path);
    
    img.img_ptr = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
    if (!img.img_ptr)
    {
        printf("Error: Failed to load texture: %s\n", path);
        error_exit("Texture loading failed");
    }
    
    img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
                                   &img.line_length, &img.endian);
    if (!img.addr)
        error_exit("Failed to get texture data address");
    
    printf("  ✓ Loaded: %dx%d pixels\n", img.width, img.height);
    
    return (img);
}

void load_all_textures(t_game *game)
{
    printf("\n=== LOADING TEXTURES ===\n");
    
    game->textures.north_img = load_texture(game->mlx, game->textures.north_path);
    game->textures.south_img = load_texture(game->mlx, game->textures.south_path);
    game->textures.east_img = load_texture(game->mlx, game->textures.east_path);
    game->textures.west_img = load_texture(game->mlx, game->textures.west_path);
    
    printf("✅ All textures loaded successfully!\n");
}

int get_texture_pixel(t_img *img, int x, int y)
{
    char *pixel;
    
    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return (0);
    
    pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    return (*(int *)pixel);
}

void free_textures(t_game *game)
{
    if (game->textures.north_img.img_ptr)
        mlx_destroy_image(game->mlx, game->textures.north_img.img_ptr);
    if (game->textures.south_img.img_ptr)
        mlx_destroy_image(game->mlx, game->textures.south_img.img_ptr);
    if (game->textures.east_img.img_ptr)
        mlx_destroy_image(game->mlx, game->textures.east_img.img_ptr);
    if (game->textures.west_img.img_ptr)
        mlx_destroy_image(game->mlx, game->textures.west_img.img_ptr);
}