#include "../inc/cub3d.h"

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
	if (game->image.img_ptr)
	{
		mlx_destroy_image(game->mlx_struct, game->image.img_ptr);
		game->image.img_ptr = NULL;
	}
	/* destroy background image if allocated */
	if (game->bg_image.img_ptr)
	{
		mlx_destroy_image(game->mlx_struct, game->bg_image.img_ptr);
		game->bg_image.img_ptr = NULL;
	}
	if (game->win_struct)
	{
		mlx_destroy_window(game->mlx_struct, game->win_struct);
		game->win_struct = NULL;
	}
	if (game->mlx_struct)
	{
		// If there are images or textures loaded, they should be destroyed here
		mlx_destroy_display(game->mlx_struct);
		free(game->mlx_struct);
		game->mlx_struct = NULL;
	}
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
	printf("north texture: %d\n", game->texture_n);
	if (game->texture_n == true)
		free(game->textures.north_texture);
	if (game->texture_s == true)
		free(game->textures.south_texture);
	if (game->texture_e == true)
		free(game->textures.east_texture);
	if (game->texture_w == true)
		free(game->textures.west_texture);
}