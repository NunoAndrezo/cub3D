/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_support3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:40:11 by nuno              #+#    #+#             */
/*   Updated: 2026/01/06 17:50:47 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	save_floor_color(t_game *game, char *line, char *tmp, bool success)
{
	int	i;

	check_for_duplicates(game, line, 'F');
	i = 1;
	while ((tmp[i] == ' ' || tmp[i] == '\t') && tmp[i] != '\0')
		i++;
	if (tmp[i] && tmp[i] >= '0' && tmp[i] <= '9')
	{
		success = save_color(game, tmp + i, 'F');
		game->color_f++;
	}
	return (success);
}

bool	save_ceiling_color(t_game *game, char *line, char *tmp, bool success)
{
	int	i;

	check_for_duplicates(game, line, 'C');
	i = 1;
	while ((tmp[i] == ' ' || tmp[i] == '\t') && tmp[i] != '\0')
		i++;
	if (tmp[i] && tmp[i] >= '0' && tmp[i] <= '9')
	{
		success = save_color(game, tmp + i, 'C');
		game->color_c++;
	}
	return (success);
}

void	print_error_and_exit(t_game *game, char *line, int fd)
{
	perror("Error\nInvalid texture or color line in map file\n");
	close(fd);
	free(line);
	free_game(game);
	exit(EXIT_FAILURE);
}

void	close_free_exit(int fd, t_game *game, char *line)
{
	perror("Error\nWrong Color in Ceiling/Floor\n");
	close(fd);
	free(line);
	free_game(game);
	exit(EXIT_FAILURE);
}

void	copy_map_helper(t_game *game, char *line, int fd, int i)
{
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
}
