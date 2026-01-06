/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:14:41 by joaoleote         #+#    #+#             */
/*   Updated: 2026/01/04 23:14:31 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_img	*get_wall_texture(t_game *game, t_column *col);
static int		get_pixel_color(t_img *img, int x, int y);
static void		draw_wall(t_game *game, t_column *col);
static void		draw_wall_support(t_game *game, t_column *col,
					t_img *tex, int tex_x);

void	draw_3dgame(t_game *game, t_column *col)
{
	if (col->column_index < 0 || col->column_index >= game->image.width)
		return ;
	if (!calculate_projection(game, col))
		return ;
	draw_floor_and_ceiling(game, col->column_index, col->start, col->end);
	draw_wall(game, col);
}

static void	draw_wall_support(t_game *game, t_column *col,
								t_img *tex, int tex_x)
{
	float	step;
	float	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = 1.0f * tex->height / (float)col->line_h;
	tex_pos = (col->start - game->image.height / 2
			+ col->line_h / 2) * step;
	y = col->start;
	while (y <= col->end)
	{
		tex_y = (int)tex_pos % tex->height;
		tex_pos += step;
		if (tex_y < 0)
			tex_y = 0;
		color = get_pixel_color(tex, tex_x, tex_y);
		my_store_pixel_in_image(&game->image, col->column_index, y, color);
		y++;
	}
}

static void	draw_wall(t_game *game, t_column *col)
{
	t_img	*tex;
	float	wall_x;
	int		tex_x;

	tex = get_wall_texture(game, col);
	if (col->hit_side == 0)
		wall_x = game->player.pos_y + col->dist * sinf(col->angle);
	else
		wall_x = game->player.pos_x + col->dist * cosf(col->angle);
	wall_x -= floorf(wall_x);
	tex_x = (int)(wall_x * (float)tex->width);
	if ((col->hit_side == 0 && cosf(col->angle) > 0)
		|| (col->hit_side == 1 && sinf(col->angle) < 0))
		tex_x = tex->width - tex_x - 1;
	draw_wall_support(game, col, tex, tex_x);
}

static t_img	*get_wall_texture(t_game *game, t_column *col)
{
	float	ray_dir_x;
	float	ray_dir_y;

	ray_dir_x = cosf(col->angle);
	ray_dir_y = sinf(col->angle);
	if (col->hit_side == 0)
	{
		if (ray_dir_x > 0)
			return (&game->textures.west);
		return (&game->textures.east);
	}
	if (ray_dir_y > 0)
		return (&game->textures.north);
	return (&game->textures.south);
}

static int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	dst = img->img_pixels_ptr
		+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
