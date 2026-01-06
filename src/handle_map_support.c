/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_support.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:15:09 by nuno              #+#    #+#             */
/*   Updated: 2026/01/06 15:08:27 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	save_parameteres(t_game *game, char *line, int fd);
static bool	parse_rgb_values(char *line, int *r, int *g, int *b);

bool	is_texture_or_color_line(t_game *game, char *line, int fd)
{
	if (!line)
	{
		perror("Error\nParsing textures and colors.\n");
		close(fd);
		free_game(game);
	}
	while (line[0] == ' ' || line[0] == '\t')
		line++;
	if (line[0] == '\0' || line[0] == '\n')
		return (true);
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		save_parameteres(game, line, fd);
		return (true);
	}
	return (false);
}

static void	save_parameteres(t_game *game, char *line, int fd)
{
	bool	success;
	int		i;

	success = true;
	i = 0;
	if (ft_strncmp(line, "NO", 2) == 0)
		north_save_parameter(game, line, i);
	else if (ft_strncmp(line, "SO", 2) == 0)
		south_save_parameter(game, line, i);
	else if (ft_strncmp(line, "WE", 2) == 0)
		west_save_parameter(game, line, i);
	else if (ft_strncmp(line, "EA", 2) == 0)
		east_save_parameter(game, line, i);
	else if (ft_strncmp(line, "F", 1) == 0)
		success = save_floor_color(game, line, i, success);
	else if (ft_strncmp(line, "C", 1) == 0)
		success = save_ceiling_color(game, line, i, success);
	else
		print_error_and_exit(game, line, fd);
	if (success == false)
		close_free_exit(fd, game, line);
}

bool	save_color(t_game *game, char *line, char type)
{
	int	r;
	int	g;
	int	b;

	r = -1;
	g = -1;
	b = -1;
	if (!parse_rgb_values(line, &r, &g, &b))
		return (false);
	if (type == 'F')
	{
		game->textures.floor_color[0] = r;
		game->textures.floor_color[1] = g;
		game->textures.floor_color[2] = b;
	}
	else if (type == 'C')
	{
		game->textures.ceiling_color[0] = r;
		game->textures.ceiling_color[1] = g;
		game->textures.ceiling_color[2] = b;
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (perror(
				"Error\nRGB color values must be between 0 and 255\n"), false);
	return (true);
}

static bool	parse_rgb_values(char *line, int *r, int *g, int *b)
{
	char	**values;
	int		i;

	values = NULL;
	values = ft_split(line, ',');
	if (!values)
	{
		free_split_values(values);
		perror("Error\nMemory allocation failed while parsing RGB values\n");
		return (false);
	}
	i = 0;
	while (values[i])
		i++;
	if (i != 3)
	{
		free_split_values(values);
		perror("Error\nRGB color line must contain exactly 3 values\n");
		return (false);
	}
	*r = ft_atoi(values[0]);
	*g = ft_atoi(values[1]);
	*b = ft_atoi(values[2]);
	free_split_values(values);
	return (true);
}
