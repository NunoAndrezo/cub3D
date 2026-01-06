/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_drawing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 03:17:39 by joaoleote         #+#    #+#             */
/*   Updated: 2026/01/05 03:18:54 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_tile_color(char c)
{
	if (c == '1')
		return (COLOR_WHITE);
	if (c == ' ')
		return (COLOR_GREY);
	return (COLOR_BLACK);
}

void	fill_tile(t_img *target, int g_x, int g_y, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < ONE_TILE_SIDE)
	{
		x = 0;
		while (x < ONE_TILE_SIDE)
		{
			my_store_pixel_in_image(target, g_x + x, g_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_tile_border(t_img *target, int g_x, int g_y)
{
	int	i;

	i = 0;
	while (i < ONE_TILE_SIDE)
	{
		my_store_pixel_in_image(target, g_x + i, g_y, COLOR_GREY);
		my_store_pixel_in_image(target, g_x + i,
			g_y + ONE_TILE_SIDE - 1, COLOR_GREY);
		my_store_pixel_in_image(target, g_x, g_y + i, COLOR_GREY);
		my_store_pixel_in_image(target, g_x + ONE_TILE_SIDE - 1, g_y + i,
			COLOR_GREY);
		i++;
	}
}
