#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
# include <signal.h>

#include "../inc/get_next_line.h"
#include "../minilibx-linux/mlx.h"

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
	char	player_orientation;
	int		x;
	int		y;

}				t_map;

typedef struct	s_game
{
	t_map		map;
	t_win		window;
	bool		is_valid_to_start;
	void		*mlx;
	void		*win;
}				t_game;

//parsing.c
void	parse(int ac, char **av);

//handle_map.c
void	handle_map(char *map_file, t_game *game);

//map_validation.c
bool	map_is_valid(t_game *game);

// initiate.c
void	initiate_and_allocate(t_game *game);

//setup_signals.c
void	setup_signals(void);


//ft_bzero.c
void	ft_bzero(void *s, size_t n);

//ft_calloc.c
void	*ft_calloc(size_t count, size_t size);

//utils.c
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);

#endif