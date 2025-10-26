#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "../inc/get_next_line.h"

void	handle_map(char *map, t_game *game);

void	parse(int ac, char **av);

typedef struct s_win
{
	void		*mlx_ptr;
	void		*window_ptr;
	int			width;
	int			height;
}				t_win;

typedef struct	s_map
{
	char	**map;
	int		x;
	int		y;
	int		map_dim_x; // are these necessary?
	int		map_dim_y; // are these necessary?

}				t_map;

typedef struct	s_game
{
	t_map		map;
	t_win		window;
}				t_game;

#endif