/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:16 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 23:00:52 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int count_and_store_number_of_lines_and_check_textures_colors(t_game *game, char *map_file);
static void copy_map(char *map_file, t_game *game);
static void allocate_map(t_game *game);

void handle_map(char *map_file, t_game *game)
{
	ft_bzero(&game->map, sizeof(t_map));
	ft_bzero(&game->textures, sizeof(t_texture));
	game->map.map_file = map_file;
	if (!game->map.map_file)
		perror("Error\nNo map file provided\n"), free_game(game), exit(EXIT_FAILURE);
	if (count_and_store_number_of_lines_and_check_textures_colors(game, game->map.map_file) <= 0)
		perror("Error\nMap file is empty\n"), free_game(game), exit(EXIT_FAILURE);
	if (!game->textures.north_texture || !game->textures.south_texture ||
		!game->textures.west_texture || !game->textures.east_texture)
		perror("Error\nMissing texture paths in map file\n"), free_game(game), exit(EXIT_FAILURE);
	if (game->texture_n == false || game->texture_s == false ||
		game->texture_w == false || game->texture_e == false ||
		game->color_f == false || game->color_c == false)
		perror("Error\nNot all required textures and colors were specified\n"), free_game(game), exit(EXIT_FAILURE);
	copy_map(game->map.map_file, game);
}

static int count_and_store_number_of_lines_and_check_textures_colors(t_game *game, char *map_file)
{
	char	*line;
	int		i;
	int		fd;
	bool	in_map;
	int		first_time;

	first_time = -1;
	i = 0;
	in_map = false;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		perror("Error\nCannot open map file\n"), free_game(game), exit(EXIT_FAILURE);
	game->map.y_max = 0;
	line = get_next_line(fd);
	while (line)
	{
		++i;
		if (is_texture_or_color_line(game, line, fd) == false)
		{
			if (first_time == -1)
			{
				first_time = 1;
				game->map.y_start = i;
			}
			in_map = true;
		}
		if (in_map == true)
			game->map.y_max++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (game->map.y_max);
}

static void copy_map(char *map_file, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 1;
	allocate_map(game);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		perror("Error\nCannot open map file\n"), free_game(game), exit(EXIT_FAILURE);
	line = get_next_line(fd);
	if (!line)
		perror("Error\nEmpty or invalid map file\n"), close(fd), free_game(game), exit(EXIT_FAILURE);
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!line)
			break ;
		if (game->map.y_start <= i)
			game->map.map[i - game->map.y_start] = ft_strdup(line);
	}
	close(fd);
}

static void	allocate_map(t_game *game)
{
	game->map.map = (char **)ft_calloc((game->map.y_max + 1), sizeof(char *));
	if (!game->map.map)
	{
		perror("Error\nMemory allocation failed\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->map.map[game->map.y_max] = NULL;
}
