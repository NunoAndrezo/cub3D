/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_support3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:40:11 by nuno              #+#    #+#             */
/*   Updated: 2026/01/06 15:01:39 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	save_floor_color(t_game *game, char *line, int i, bool success)
{
	i = 1;
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	if (line[i] && line[i] >= '0' && line[i] <= '9')
	{
		check_for_duplicates(game, line, 'F');
		success = save_color(game, line + i, 'F');
		game->color_f++;
	}
	return (success);
}

bool	save_ceiling_color(t_game *game, char *line, int i, bool success)
{
	i = 1;
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	if (line[i] && line[i] >= '0' && line[i] <= '9')
	{
		check_for_duplicates(game, line, 'C');
		success = save_color(game, line + i, 'C');
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
