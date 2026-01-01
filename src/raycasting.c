/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:14:49 by joaoleote         #+#    #+#             */
/*   Updated: 2026/01/01 23:00:18 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_ray(t_game *g, t_ray *r, float angle);
static void	choose_hit(t_game *g, t_ray *r, int column);

void	lets_see_them_rays(t_game *g)
{
	int		i;
	int		n;
	float	step;
	float	angle;

	n = g->ray.num_rays;
	if (n <= 0)
		n = g->image.width;
	step = g->player.fov_degrees / (float)n;
	i = 0;
	while (i < n)
	{
		angle = g->player.player_angle - g->player.fov_degrees 
			/ 2.0f + i * step;
		init_ray(g, &g->ray, deg_to_rad(angle));
		cast_ray(g, &g->ray);
		choose_hit(g, &g->ray, i);
		i++;
	}
	g->ray.num_rays = n;
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

static void	choose_hit(t_game *g, t_ray *r, int column)
{
/*	if (g->ray.debug_rays)
		draw_rays(g, r->ray_x, r->ray_y, r->hit_side);*/
	draw_3Dgame(g, r->angle, r->distance, r->hit_side, column);
}
