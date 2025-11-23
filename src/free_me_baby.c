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
	// Free other allocated resources if any
}