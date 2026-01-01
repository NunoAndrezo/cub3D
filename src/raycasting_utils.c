/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 16:34:05 by joaoleote         #+#    #+#             */
/*   Updated: 2026/01/01 16:46:03 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_wall(t_game *g, int x, int y)
{
	if (y < 0 || y >= g->map.y_max)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(g->map.map[y]))
		return (1);
	if (g->map.map[y][x] == '1')
		return (1);
	return (0);
}

void	draw_rays(t_game *g, float x, float y, int side)
{
	int	color;
	int px;
	int py;

	px = (int)(x * ONE_TILE_SIDE);
	py = (int)(y * ONE_TILE_SIDE);
	color = COLOR_YELLOW;
	if (side == 0)
		color = COLOR_RED;
	if (side == 1)
		color = COLOR_BLUE;
	my_store_pixel_in_image(&g->image, px, py, color);
}

void	cast_ray(t_game *g, t_ray *r)
{
	int	map_x;
	int	map_y;

	map_x = (int)r->ray_x;
	map_y = (int)r->ray_y;
	while (!is_wall(g, map_x, map_y))
		dda_step(r, &map_x, &map_y);
	r->distance = calc_dist(g, r, map_x, map_y);
	r->ray_x = g->player.pos_x + r->x_step * r->distance;
	r->ray_y = g->player.pos_y + r->y_step * r->distance;
}

void	init_ray_dir_pos(t_game *g, t_ray *r, float angle,
						float *pos_x, float *pos_y, int *map_x, int *map_y)
{
	r->angle = angle;
	r->x_step = cosf(angle);
	r->y_step = sinf(angle);
	*pos_x = g->player.pos_x;
	*pos_y = g->player.pos_y;
	r->ray_x = *pos_x;
	r->ray_y = *pos_y;
	*map_x = (int)(*pos_x);
	*map_y = (int)(*pos_y);
}

void	init_ray_distances(t_ray *r, float pos_x, float pos_y, int map_x, 
							int map_y)
{
	if (r->x_step != 0.0f)
		r->delta_dist_x = fabsf(1.0f / r->x_step);
	else
		r->delta_dist_x = 1000000.0f;
	if (r->y_step != 0.0f)
		r->delta_dist_y = fabsf(1.0f / r->y_step);
	else
		r->delta_dist_y = 1000000.0f;
	if (r->x_step < 0)
		r->side_dist_x = (pos_x - map_x) * r->delta_dist_x;
	else
		r->side_dist_x = (map_x + 1.0f - pos_x) * r->delta_dist_x;
	if (r->y_step < 0)
		r->side_dist_y = (pos_y - map_y) * r->delta_dist_y;
	else
		r->side_dist_y = (map_y + 1.0f - pos_y) * r->delta_dist_y;
}
