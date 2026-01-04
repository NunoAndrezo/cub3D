/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d_game_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:43:25 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 13:23:32 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	calculate_projection(t_game *g, float ray_angle, float dist,
						int *start, int *end, int *line_height)
{
	float	corrected;
	float	player_rad;
	int		line_h;

	player_rad = deg_to_rad(g->player.player_angle);
	corrected = dist * cosf(ray_angle - player_rad);
	if (corrected < 0.0001f)
		corrected = 0.0001f;
	line_h = (int)(g->image.height / corrected);
	*line_height = line_h;
	if (line_h < 2)
		return (0);
	*start = -line_h / 2 + g->image.height / 2;
	*end = line_h / 2 + g->image.height / 2;
	if (*start < 0)
		*start = 0;
	if (*end >= g->image.height)
		*end = g->image.height - 1;
	return (1);
}

void	draw_floor_and_ceiling(t_img *img, int x,
			int start, int end, t_game *game)
{
	int	y;

	y = 0;
	while (y < start)
	{
		my_store_pixel_in_image(img,
			x, y, rgb_to_color(game->textures.ceiling_color));
		y++;
	}
	y = end + 1;
	while (y < img->height)
	{
		my_store_pixel_in_image(img,
			x, y, rgb_to_color(game->textures.floor_color));
		y++;
	}
}
