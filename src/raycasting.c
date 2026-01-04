/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:14:49 by joaoleote         #+#    #+#             */
/*   Updated: 2026/01/04 23:26:13 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_ray(t_game *g, t_ray *r, float angle);

void lets_see_them_rays(t_game *g)
{
	int		i;
	int		n;
	float	step;
	float	angle;

	n = g->image.width;
	if (g->ray.num_rays > 0 && g->ray.num_rays < g->image.width)
		n = g->ray.num_rays;
	g->ray.num_rays = n;
	step = g->player.fov_degrees / (float)n;
	i = 0;
	while (i < n)
	{
		angle = g->player.player_angle - g->player.fov_degrees / 2.0f
		+ i * step;
		init_ray(g, &g->ray, deg_to_rad(angle));
		cast_ray(g, &g->ray);
		draw_3dgame(g, g->ray.angle, g->ray.distance, g->ray.hit_side, i);
		i++;
	}
}

static void	init_ray(t_game *g, t_ray *r, float angle)
{
	float	pos_x;
	float	pos_y;
	int		map_x;
	int		map_y;

	init_ray_dir_pos(g, r, angle, &pos_x, &pos_y, &map_x, &map_y);
	init_ray_distances(r, pos_x, pos_y, map_x, map_y);
}

//dda means digital differential analyzer,
//for dummies: it is a line drawing algorithm that incrementally
//determines the points of an n-dimensional raster that should be
//selected in order to form a close approximation
//to a straight line between two points
void	dda_step(t_ray *r, int *map_x, int *map_y)
{
	if (r->side_dist_x < r->side_dist_y)
	{
		r->side_dist_x += r->delta_dist_x;
		if (r->x_step < 0)
			*map_x -= 1;
		else
			*map_x += 1;
		r->hit_side = 0;
	}
	else
	{
		r->side_dist_y += r->delta_dist_y;
		if (r->y_step < 0)
			*map_y -= 1;
		else
			*map_y += 1;
		r->hit_side = 1;
	}
}

float	calc_dist(t_game *g, t_ray *r, int map_x, int map_y)
{
	if (r->hit_side == 0)
		return ((map_x - g->player.pos_x + (r->x_step < 0)) / r->x_step);
	return ((map_y - g->player.pos_y + (r->y_step < 0)) / r->y_step);
}
