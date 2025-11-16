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

typedef enum e_game_state
{
	STATE_MENU,
	STATE_OPTIONS,
	STATE_PLAYING,
	STATE_PAUSED
}	t_game_state;

/* simple image container */
typedef struct s_img
{
void 	*img_ptr;
int		w;
int		h;
char	*path;
}	t_img;

typedef struct	s_map
{
	char	**map;
	char	*map_file;
	char	player_orientation;
	int		player_start_x;
	int		player_start_y;
	int		y_max;

}				t_map;

typedef struct	s_game
{
	t_map				map;
	void				*mlx;
	void				*win;
	int					win_w; /* current window width */
	int					win_h; /* current window height */
	t_game_state		state;
	t_img				menu_image;
	t_img				cursor; /* small arrow to indicate menu selection */
	int                 menu_selection; /* 0=start,1=options,2=exit */
	/* cursor animation removed; cursor is static */
}				t_game;

//parsing.c
void	parse(int ac, char **av);

//handle_map.c
void	handle_map(char *map_file, t_game *game);

//map_validation.c
bool	map_is_valid(t_game *game);

// initiate.c
void	initiate_game(t_game *game);

//setup_signals.c
void	setup_signals(void);


//ft_bzero.c
void	ft_bzero(void *s, size_t n);

//ft_calloc.c
void	*ft_calloc(size_t count, size_t size);

//utils.c
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);

//flood_fill.c
bool	flood_fill(t_game *game);

#endif