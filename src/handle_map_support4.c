/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_support4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:43:26 by nneves-a          #+#    #+#             */
/*   Updated: 2026/01/06 17:51:51 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_for_duplicates(t_game *game, char *line, char type)
{
	bool	has_duplicate;

	has_duplicate = false;
	if (type == 'N' && game->texture_n > 0)
		has_duplicate = true;
	else if (type == 'S' && game->texture_s > 0)
		has_duplicate = true;
	else if (type == 'W' && game->texture_w > 0)
		has_duplicate = true;
	else if (type == 'E' && game->texture_e > 0)
		has_duplicate = true;
	else if (type == 'F' && game->color_f > 0)
		has_duplicate = true;
	else if (type == 'C' && game->color_c > 0)
		has_duplicate = true;
	if (has_duplicate)
	{
		perror("Error\nDuplicate texture or color definition found!\n");
		free(line);
		free_game(game);
		exit(EXIT_FAILURE);
	}
}
