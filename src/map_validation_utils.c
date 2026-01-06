/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 02:07:46 by joaoleote         #+#    #+#             */
/*   Updated: 2026/01/05 02:09:22 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (true);
	if (is_player_char(c))
		return (true);
	return (false);
}

int	find_max_len(t_game *game)
{
	int	j;
	int	i;
	int	max_len;

	j = 0;
	max_len = 0;
	while (j < game->map.y_max)
	{
		i = 0;
		while (game->map.map[j][i])
			i++;
		if (i > max_len)
			max_len = i;
		j++;
	}
	return (max_len);
}

bool	pad_row_to_max(t_game *game, int j, int max_len)
{
	char	*new_row;

	while ((int)ft_strlen(game->map.map[j]) < max_len)
	{
		new_row = ft_strjoin_char(game->map.map[j], ' ');
		if (new_row == NULL)
			return (false);
		free(game->map.map[j]);
		game->map.map[j] = new_row;
	}
	return (true);
}
