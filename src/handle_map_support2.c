/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_support2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:35:22 by nuno              #+#    #+#             */
/*   Updated: 2026/01/06 15:01:30 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	north_save_parameter(t_game *game, char *line, int i)
{
	check_for_duplicates(game, line, 'N');
	i = 2;
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	if (line[i])
	{
		game->textures.north_texture = ft_strdup(line + i);
		strip_newline(game->textures.north_texture);
		game->texture_n++;
	}
}

void	south_save_parameter(t_game *game, char *line, int i)
{
	check_for_duplicates(game, line, 'S');
	i = 2;
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	if (line[i])
	{
		game->textures.south_texture = ft_strdup(line + i);
		strip_newline(game->textures.south_texture);
		game->texture_s++;
	}
}

void	west_save_parameter(t_game *game, char *line, int i)
{
	i = 2;
	check_for_duplicates(game, line, 'W');
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	if (line[i])
	{
		game->textures.west_texture = ft_strdup(line + i);
		strip_newline(game->textures.west_texture);
		game->texture_w++;
	}
}

void	east_save_parameter(t_game *game, char *line, int i)
{
	check_for_duplicates(game, line, 'E');
	i = 2;
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	if (line[i])
	{
		game->textures.east_texture = ft_strdup(line + i);
		strip_newline(game->textures.east_texture);
		game->texture_e++;
	}
}
