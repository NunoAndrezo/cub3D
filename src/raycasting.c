/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:14:49 by joaoleote         #+#    #+#             */
/*   Updated: 2026/01/06 03:21:23 by joaoleote        ###   ########.fr       */
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
		choose_hit(g, &g->ray, i);
		i++;
	}
}

static void	init_ray(t_game *g, t_ray *r, float angle)
{
	init_ray_dir_pos(g, r, angle);
	init_ray_distances(r);
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
	t_column	col;

	col.angle = r->angle;
	col.dist = r->distance;
	col.hit_side = r->hit_side;
	col.column_index = column;
	draw_3dgame(g, &col);
}
