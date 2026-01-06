/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:33 by nuno              #+#    #+#             */
/*   Updated: 2026/01/06 03:20:51 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	check_max_dimensions(t_game *game);

int	main(int ac, char **av)
{
	t_game	game;

	parse(ac, av);
	setup_signals();
	ft_bzero(&game, sizeof(t_game));
	handle_map(av[1], &game);
	if (map_is_valid(&game) == true && last_map_adjustments(&game)
		&& check_max_dimensions(&game))
	{
		initiate_game(&game);
		load_game(&game);
		start_gaming(&game);
	}
	else
	{
		free_game(&game);
		perror("Error\nMap validation failed. Cannot start the game.\n");
		return (1);
	}
	free_game(&game);
	return (0);
}

static bool	check_max_dimensions(t_game *game)
{
	if (WWIDTH == 1920 && WHEIGHT == 1000)
	{
		if (game->map.x_max > 110 || game->map.y_max > 60
			|| (game->map.x_max <= 2 && game->map.y_max <= 2))
		{
			perror("Error\n");
			perror("Map dimensions exceed maximum allowed size of 110x50.\n");
			free_game(game);
			exit(EXIT_FAILURE);
		}
	}
	return (true);
}
