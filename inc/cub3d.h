#ifndef CUB3D_H
#define CUB3D_H

#include "../inc/handle_map.h"
#include "../inc/parsing.h"

typedef struct	s_map
{
	char	**map;
	int		x;
	int		y;

}				t_map;

typedef struct	s_game
{
	t_map		map;
}				t_game;

#endif