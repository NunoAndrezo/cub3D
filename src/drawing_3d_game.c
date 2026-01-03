/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:14:41 by joaoleote         #+#    #+#             */
/*   Updated: 2026/01/03 14:30:04 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_img	*get_wall_texture(t_game *game, int hit_side, float angle);
static int		get_pixel_color(t_img *img, int x, int y);

void	draw_3Dgame(t_game *game, float angle, float best_dist,
					int hit_side, int column_index)
{
	int	x;
	int	draw_start;
	int	draw_end;
	int	line_h;

	x = column_index;
	if (x < 0 || x >= game->image.width)
		return;
	if (!calculate_projection(game, angle, best_dist, &draw_start, 
		&draw_end, &line_h))
		return;
	draw_floor_and_ceiling(&game->image, x, draw_start, draw_end, game);
	draw_wall(&game->image, x, draw_start, draw_end, line_h, game, angle, best_dist, hit_side);
}

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
	*end   =  line_h / 2 + g->image.height / 2;
	if (*start < 0)
		*start = 0;
	if (*end >= g->image.height)
		*end = g->image.height - 1;
	return (1);
}

void	draw_floor_and_ceiling(t_img *img, int x, int start, int end, t_game *game)
{
	int	y;

	y = 0;
	while (y < start)
	{
		my_store_pixel_in_image(img, x, y, rgb_to_color(game->textures.ceiling_color));
		y++;
	}
	y = end + 1;
	while (y < img->height)
	{
		my_store_pixel_in_image(img, x, y, rgb_to_color(game->textures.floor_color));
		y++;
	}
}

void	draw_wall(t_img *img, int x, int start, int end, int line_h, t_game *game, float angle, float dist, int hit_side)
{
	t_img	*tex;
	float	wall_x;
	int		tex_x;
	float	step;
	float	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	tex = get_wall_texture(game, hit_side, angle);
	if (hit_side == 0)
		wall_x = game->player.pos_y + dist * sinf(angle);
	else
		wall_x = game->player.pos_x + dist * cosf(angle);
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (float)tex->width);
	if ((hit_side == 0 && cosf(angle) > 0) || (hit_side == 1 && sinf(angle) < 0))
		tex_x = tex->width - tex_x - 1;

	step = 1.0 * tex->height / line_h;
	tex_pos = (start - game->image.height / 2 + line_h / 2) * step;

	y = start;
	while (y <= end)
	{
		tex_y = (int)tex_pos % tex->height;
		tex_pos += step;
		if (tex_y < 0)
			tex_y = 0;
		color = get_pixel_color(tex, tex_x, tex_y);
		my_store_pixel_in_image(img, x, y, color);
		y++;
	}
}

static t_img	*get_wall_texture(t_game *game, int hit_side, float angle)
{
	float	ray_dir_x;
	float	ray_dir_y;

	ray_dir_x = cosf(angle);
	ray_dir_y = sinf(angle);
	if (hit_side == 0)
	{
		if (ray_dir_x > 0)
			return (&game->textures.west);
		else
			return (&game->textures.east);
	}
	else
	{
		if (ray_dir_y > 0)
			return (&game->textures.north);
		else
			return (&game->textures.south);
	}
}

static int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	dst = img->img_pixels_ptr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
