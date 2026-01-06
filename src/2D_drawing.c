/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:25:48 by nuno              #+#    #+#             */
/*   Updated: 2026/01/05 03:22:13 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_player(t_game *game)
{
	int	size;
	int	player_pixel_x;
	int	player_pixel_y;
	int	y;
	int	x;

	size = 3;
	player_pixel_x = (int)(game->player.pos_x * ONE_TILE_SIDE);
	player_pixel_y = (int)(game->player.pos_y * ONE_TILE_SIDE);
	y = -size;
	while (y <= size)
	{
		x = -size;
		while (x <= size)
		{
			my_store_pixel_in_image(&game->image, player_pixel_x + x,
				player_pixel_y + y, COLOR_YELLOW);
			x++;
		}
		y++;
	}
}

void	draw_map_to_image(t_game *game, t_img *target)
{
	int	real_y;
	int	real_x;
	int	g_x;
	int	g_y;

	(void)target;
	real_y = 0;
	while (game->map.map[real_y])
	{
		real_x = 0;
		while (game->map.map[real_y][real_x])
		{
			g_y = real_y * ONE_TILE_SIDE;
			g_x = real_x * ONE_TILE_SIDE;
			fill_tile(target, g_x, g_y,
				get_tile_color(game->map.map[real_y][real_x]));
			draw_tile_border(target, g_x, g_y);
			real_x++;
		}
		real_y++;
	}
}

void	my_store_pixel_in_image(t_img *image, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	offset = (image->line_length * y) + (x * (image->bits_per_pixel / 8));
	*(unsigned int *)(image->img_pixels_ptr + offset) = color;
}
