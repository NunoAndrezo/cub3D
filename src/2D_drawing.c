/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:25:48 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 14:46:02 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_player(t_game *game)
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
	x = -size;
	// draw the player as a square
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
	int g_x;
	int g_y;
	int	color;

	(void)target;
	real_y = 0;
	int xrow;
	while (game->map.map[real_y])
	{
		real_x = 0;
		xrow = ft_strlen(game->map.map[real_y]);
		while (real_x < xrow)
		{
			g_y = real_y * ONE_TILE_SIDE;
			g_x = real_x * ONE_TILE_SIDE;
			if (game->map.map[real_y][real_x] == '1')
				color = COLOR_WHITE;
			else if (game->map.map[real_y][real_x] == ' ')
				color = COLOR_GREY;
			else
				color = COLOR_BLACK;
			for (int y = 0; y < ONE_TILE_SIDE; y++)
				for (int x = 0; x < ONE_TILE_SIDE; x++)
					my_store_pixel_in_image(target, g_x + x, g_y + y, color);
			// draw cell borders
			for (int i = 0; i < ONE_TILE_SIDE; i++)
			{
				my_store_pixel_in_image(target, g_x + i, g_y, COLOR_GREY);
				my_store_pixel_in_image(target, g_x + i,
						g_y + ONE_TILE_SIDE - 1, COLOR_GREY);
				my_store_pixel_in_image(target, g_x, g_y + i, COLOR_GREY);
				my_store_pixel_in_image(target, g_x + ONE_TILE_SIDE - 1,
						g_y + i, COLOR_GREY);
			}
			real_x++;
		}
		real_y++;
	}
}

// Detailed explanation:
// This function calculates the memory offset
//for a pixel at coordinates (x, y) in the image.
// it calculates the offset in the image's pixel game array using the formula:
// offset = (line_length * y) + (x * (bits_per_pixel / 8))
// Here, line_length is the number of bytes in a single
//row of pixels, y is the row number,
//x is the column number, and bits_per_pixel / 8 converts bits to bytes.
// Finally, it stores the color value at the calculated offset
//by casting the offset pointer
//to an unsigned int pointer and dereferencing it to set the color
void	my_store_pixel_in_image(t_img *image, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	offset = (image->line_length * y) + (x * (image->bits_per_pixel / 8));
	*(unsigned int *)(image->img_pixels_ptr + offset) = color;
}
