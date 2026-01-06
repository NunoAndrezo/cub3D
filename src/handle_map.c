/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:16 by nuno              #+#    #+#             */
/*   Updated: 2026/01/06 11:27:47 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	count_num_of_lines_and_check_textures(t_game *game, char *map_file);
static void	copy_map(char *map_file, t_game *game);
static void	allocate_map(t_game *game);
static void	count_helper(t_game *game, char *line, int i, int fd);

void	handle_map(char *map_file, t_game *game)
{
	ft_bzero(&game->map, sizeof(t_map));
	ft_bzero(&game->textures, sizeof(t_texture));
	game->map.map_file = map_file;
	if (!game->map.map_file)
	{
		perror("Error\nNo map file provided\n");
		exit(EXIT_FAILURE);
	}
	if (count_num_of_lines_and_check_textures(game, game->map.map_file) <= 0)
	{
		perror("Error\nMap file is empty\n");
		exit(EXIT_FAILURE);
	}
	if (!game->textures.north_texture || !game->textures.south_texture
		|| !game->textures.west_texture || !game->textures.east_texture)
		(perror("Error\nMissing texture paths in map file\n"),
			free_game(game), exit(EXIT_FAILURE));
	if (game->texture_n == false || game->texture_s == false
		|| game->texture_w == false || game->texture_e == false
		|| game->color_f == false || game->color_c == false)
		(perror("Error\nNot all required textures and colors were specified\n"),
			free_game(game), exit(EXIT_FAILURE));
	copy_map(game->map.map_file, game);
}

static int	count_num_of_lines_and_check_textures(t_game *game, char *map_file)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		(perror("Error\nCannot open map file\n"), exit(EXIT_FAILURE));
	game->map.y_max = 0;
	line = get_next_line(fd);
	count_helper(game, line, i, fd);
	return (close(fd), game->map.y_max);
}

static void	count_helper(t_game *game, char *line, int i, int fd)
{
	bool	in_map;
	int		first_time;

	first_time = -1;
	in_map = false;
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
}

static void	copy_map(char *map_file, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 1;
	allocate_map(game);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		(perror("Error\nCannot open map file\n"), exit(EXIT_FAILURE));
	line = get_next_line(fd);
	if (!line)
		(perror("Error\nEmpty or invalid map file\n"),
			close(fd), exit(EXIT_FAILURE));
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	copy_map_helper(game, line, fd, i);
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
