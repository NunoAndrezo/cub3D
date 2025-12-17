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
	if (!game->textures.north_texture)
	{
		perror("Error\nNorth texture path is NULL.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->textures.north_texture = mlx_xpm_file_to_image(game->mlx_struct, game->textures.north_texture, &game->textures.texture_w, &game->textures.texture_h);
	if (!game->textures.north_texture)
	{
		perror("Error\nFailed to load north texture.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

static void	load_south_texture(t_game *game)
{
	if (!game->textures.south_texture)
	{
		perror("Error\nSouth texture path is NULL.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->textures.south_texture = mlx_xpm_file_to_image(game->mlx_struct, game->textures.south_texture, &game->textures.texture_w, &game->textures.texture_h);
	if (!game->textures.south_texture)
	{
		perror("Error\nFailed to load south texture.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

static void	load_west_texture(t_game *game)
{
	if (!game->textures.west_texture)
	{
		perror("Error\nWest texture path is NULL.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->textures.west_texture = mlx_xpm_file_to_image(game->mlx_struct, game->textures.west_texture, &game->textures.texture_w, &game->textures.texture_h);
	if (!game->textures.west_texture)
	{
		perror("Error\nFailed to load west texture.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

static void	load_east_texture(t_game *game)
{
	if (!game->textures.east_texture)
	{
		perror("Error\nEast texture path is NULL.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->textures.east_texture = mlx_xpm_file_to_image(game->mlx_struct, game->textures.east_texture, &game->textures.texture_w, &game->textures.texture_h);
	if (!game->textures.east_texture)
	{
		perror("Error\nFailed to load east texture.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
}