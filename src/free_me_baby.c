#include "../inc/cub3d.h"

static void free_textures_paths(t_game *game);
static void free_texture_images(t_game *game);

void	free_game(t_game *game)
{
	int	i;

	if (game->map.map)
	{
		i = 0;
		while (game->map.map[i])
		{
			free(game->map.map[i]);
			i++;
		}
		free(game->map.map);
		game->map.map = NULL;
	}
	if (game->win_struct)
	{
		mlx_destroy_window(game->mlx_struct, game->win_struct);
		game->win_struct = NULL;
	}
	if (game->mlx_struct)
	{
		free_textures_paths(game);
		free_texture_images(game);
		mlx_destroy_display(game->mlx_struct);
		free(game->mlx_struct);
		game->mlx_struct = NULL;
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
	if (game->textures.north_img)
	{
		mlx_destroy_image(game->mlx_struct, game->textures.north_img);
		game->textures.north_img = NULL;
	}
	if (game->textures.south_img)
	{
		mlx_destroy_image(game->mlx_struct, game->textures.south_img);
		game->textures.south_img = NULL;
	}
	if (game->textures.west_img)
	{
		mlx_destroy_image(game->mlx_struct, game->textures.west_img);
		game->textures.west_img = NULL;
	}
	if (game->textures.east_img)
	{
		mlx_destroy_image(game->mlx_struct, game->textures.east_img);
		game->textures.east_img = NULL;
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
