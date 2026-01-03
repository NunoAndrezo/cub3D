#include "../inc/cub3d.h"

static void	load_texture(t_game *game, t_img *img, char *path);

void	load_game(t_game *game)
{
	load_texture(game, &game->textures.north, game->textures.north_texture);
	load_texture(game, &game->textures.south, game->textures.south_texture);
	load_texture(game, &game->textures.west, game->textures.west_texture);
	load_texture(game, &game->textures.east, game->textures.east_texture);
}

static void	load_texture(t_game *game, t_img *img, char *path)
{
	int		fd;

	if (!path)
	{
		perror("Error\nTexture path is NULL.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nTexture file does not exist or cannot be opened.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	close(fd);
	img->img_ptr = mlx_xpm_file_to_image(game->mlx_struct, path, &img->width, &img->height);
	if (!img->img_ptr)
	{
		perror("Error\nFailed to load texture.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	img->img_pixels_ptr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
}
