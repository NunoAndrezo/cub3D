#include "../inc/cub3d.h"

static void free_game_map(t_game *game);
static void free_textures_paths(t_game *game);
static void free_texture_images(t_game *game);

void	free_game(t_game *game)
{
	free_game_map(game);
	free_textures_paths(game);
	free_texture_images(game);
	if (game->win_struct)
	{
		mlx_destroy_window(game->mlx_struct, game->win_struct);
		game->win_struct = NULL;
	}
	if (game->mlx_struct)
	{
		mlx_destroy_display(game->mlx_struct);
		free(game->mlx_struct);
		game->mlx_struct = NULL;
	}
}

static void free_game_map(t_game *game)
{
	int	i;

	if (game->map.map)
	{
		i = 0;
		while (i < game->map.y_max)
		{
			if (game->map.map[i])
			{
				free(game->map.map[i]);
				game->map.map[i] = NULL;
			}
			i++;
		}
		free(game->map.map);
		game->map.map = NULL;
	}
}

static void free_textures_paths(t_game *game)
{
	if (game->textures.north_texture)
	{
		free(game->textures.north_texture);
		game->textures.north_texture = NULL;
	}
	if (game->textures.south_texture)
	{
		free(game->textures.south_texture);
		game->textures.south_texture = NULL;
	}
	if (game->textures.west_texture)
	{
		free(game->textures.west_texture);
		game->textures.west_texture = NULL;
	}
	if (game->textures.east_texture)
	{
		free(game->textures.east_texture);
		game->textures.east_texture = NULL;
	}
}

static void free_texture_images(t_game *game)
{
	if (game->textures.north.img_ptr)
	{
		mlx_destroy_image(game->mlx_struct, game->textures.north.img_ptr);
		game->textures.north.img_ptr = NULL;
	}
	if (game->textures.south.img_ptr)
	{
		mlx_destroy_image(game->mlx_struct, game->textures.south.img_ptr);
		game->textures.south.img_ptr = NULL;
	}
	if (game->textures.west.img_ptr)
	{
		mlx_destroy_image(game->mlx_struct, game->textures.west.img_ptr);
		game->textures.west.img_ptr = NULL;
	}
	if (game->textures.east.img_ptr)
	{
		mlx_destroy_image(game->mlx_struct, game->textures.east.img_ptr);
		game->textures.east.img_ptr = NULL;
	}
	if (game->image.img_ptr)
	{
		mlx_destroy_image(game->mlx_struct, game->image.img_ptr);
		game->image.img_ptr = NULL;
	}
	if (game->bg_image.img_ptr)
	{
		mlx_destroy_image(game->mlx_struct, game->bg_image.img_ptr);
		game->bg_image.img_ptr = NULL;
	}
}
