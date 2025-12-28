#include "../inc/cub3d.h"

static void	load_textures(t_game *game);
static void	load_north_texture(t_game *game);
static void	load_south_texture(t_game *game);
static void	load_west_texture(t_game *game);
static void	load_east_texture(t_game *game);

void	load_game(t_game *game)
{
	load_textures(game);
}

static void	load_textures(t_game *game)
{
	load_north_texture(game);
	load_south_texture(game);
	load_west_texture(game);
	load_east_texture(game);
}
static void	load_north_texture(t_game *game)
{
	int		fd;

	if (!game->textures.north_texture)
	{
		perror("Error\nNorth texture path is NULL.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	fd = open(game->textures.north_texture, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nNorth texture file does not exist or cannot be opened.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->textures.north_img = mlx_xpm_file_to_image(game->mlx_struct, game->textures.north_texture, &game->textures.texture_w, &game->textures.texture_h);
	close(fd);
	if (!game->textures.north_img)
	{
		perror("Error\nFailed to load north texture.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

static void	load_south_texture(t_game *game)
{
	int		fd;

	if (!game->textures.south_texture)
	{
		perror("Error\nSouth texture path is NULL.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	fd = open(game->textures.south_texture, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nSouth texture file does not exist or cannot be opened.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->textures.south_img = mlx_xpm_file_to_image(game->mlx_struct, game->textures.south_texture, &game->textures.texture_w, &game->textures.texture_h);
	close(fd);
	if (!game->textures.south_img)
	{
		perror("Error\nFailed to load south texture.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

static void	load_west_texture(t_game *game)
{
	int		fd;

	if (!game->textures.west_texture)
	{
		perror("Error\nWest texture path is NULL.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	fd = open(game->textures.west_texture, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nWest texture file does not exist or cannot be opened.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->textures.west_img = mlx_xpm_file_to_image(game->mlx_struct, game->textures.west_texture, &game->textures.texture_w, &game->textures.texture_h);
	close(fd);
	if (!game->textures.west_img)
	{
		perror("Error\nFailed to load west texture.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

static void	load_east_texture(t_game *game)
{
	int		fd;

	if (!game->textures.east_texture)
	{
		perror("Error\nEast texture path is NULL.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	fd = open(game->textures.east_texture, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nEast texture file does not exist or cannot be opened.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->textures.east_img = mlx_xpm_file_to_image(game->mlx_struct, game->textures.east_texture, &game->textures.texture_w, &game->textures.texture_h);
	close(fd);
	if (!game->textures.east_img)
	{
		perror("Error\nFailed to load east texture.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
}