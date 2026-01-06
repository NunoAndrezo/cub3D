/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_support.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:15:09 by nuno              #+#    #+#             */
/*   Updated: 2026/01/05 03:40:46 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	save_parameteres(t_game *game, char *line, int fd);
static bool	save_color(t_game *game, char *line, char type);
static bool	parse_rgb_values(char *line, int *r, int *g, int *b);

bool	is_texture_or_color_line(t_game *game, char *line, int fd)
{
	if (!line)
	{
		perror("Error\nParsing textures and colors.\n");
		exit(1);
	}
	if (line[0] == '\0' || line[0] == '\n' || line[0] == ' ' || line[0] == '\t')
		return (true);
	else if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
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
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		i = 2;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i])
		{
			game->textures.north_texture = ft_strdup(line + i);
			strip_newline(game->textures.north_texture);
			game->texture_n = true;
		}
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		i = 2;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i])
		{
			game->textures.south_texture = ft_strdup(line + i);
			strip_newline(game->textures.south_texture);
			game->texture_s = true;
		}
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		i = 2;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i])
		{
			game->textures.west_texture = ft_strdup(line + i);
			strip_newline(game->textures.west_texture);
			game->texture_w = true;
		}
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		i = 2;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i])
		{
			game->textures.east_texture = ft_strdup(line + i);
			strip_newline(game->textures.east_texture);
			game->texture_e = true;
		}
	}
	else if (ft_strncmp(line, "F", 1) == 0)
	{
		i = 1;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i] && line[i] >= '0' && line[i] <= '9')
		{
			success = save_color(game, line + i, 'F');
			game->color_f = true;
		}
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		i = 1;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i] && line[i] >= '0' && line[i] <= '9')
		{
			success = save_color(game, line + i, 'C');
			game->color_c = true;
		}
	}
	else
	{
		perror("Error\nInvalid texture or color line in map file\n");
		close(fd);
		free(line);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	if (success == false)
	{
		close(fd);
		free(line);
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

static bool	save_color(t_game *game, char *line, char type)
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
		return (perror("Error\nRGB color values must be between 0 and 255\n"), false);
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
