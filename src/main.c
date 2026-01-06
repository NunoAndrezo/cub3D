/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:33 by nuno              #+#    #+#             */
/*   Updated: 2026/01/06 18:11:09 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	check_max_dimensions(t_game *game);
static void	just_one_more_checker(t_game *game);
static void	last_checker(t_game *game);
static void	check_corners(t_game *game, int x, int y);

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
		just_one_more_checker(&game);
		last_checker(&game);
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
			perror(
				"Error\nMap dimensions exceed maximum allowed size.\n");
			free_game(game);
			exit(EXIT_FAILURE);
		}
	}
	return (true);
}

static void	just_one_more_checker(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.y_max)
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == '0')
				check_corners(game, x, y);
			x++;
		}
		y++;
	}
}

static void	check_corners(t_game *game, int x, int y)
{
	if (y - 1 < 0 || y + 1 >= game->map.y_max
		|| x - 1 < 0 || x + 1 >= game->map.x_max)
	{
		perror("Error\nMap is invalid!\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	if (game->map.map[y - 1][x] == ' ' || game->map.map[y + 1][x] == ' '
		|| game->map.map[y][x - 1] == ' ' || game->map.map[y][x + 1] == ' ')
	{
		perror("Error\nMap is invalid!\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

static void	last_checker(t_game *game)
{
	int	x;

	x = 0;
	while (game->map.map[game->map.y_max -1][x])
	{
		if (game->map.map[game->map.y_max -1][x] != ' '
			&& game->map.map[game->map.y_max -1][x] != '1')
		{
			perror("Error\nMap is invalid!\n");
			free_game(game);
			exit(EXIT_FAILURE);
		}
		x++;
	}
}
