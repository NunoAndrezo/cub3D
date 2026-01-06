/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:40 by nuno              #+#    #+#             */
/*   Updated: 2026/01/05 01:16:21 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	key_press(int key_sym, t_game *game);
static int	key_release(int key_sym, t_game *game);
static int	button_x_on_window(void *param);

void	handle_mlx_events(t_game *game)
{
	mlx_hook(game->win_struct, 2, 1L << 0, key_press, game);
	mlx_hook(game->win_struct, 3, 1L << 1, key_release, game);
	mlx_hook(game->win_struct, 17, 1L << 0, button_x_on_window, game);
}

static int	key_press(int key_sym, t_game *game)
{
	handle_key_press(key_sym, game);
	return (0);
}

static int	key_release(int key_sym, t_game *game)
{
	handle_key_release(key_sym, game);
	return (0);
}

static int	button_x_on_window(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	free_game(g);
	exit(0);
	return (0);
}
