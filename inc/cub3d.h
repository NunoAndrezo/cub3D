#ifndef CUB3D_H
#define CUB3D_H

#ifndef WWIDTH
#define WWIDTH 1024
#endif
#ifndef WHEIGHT
#define WHEIGHT 512
#endif

#ifndef PI_VALUE
#define PI_VALUE 3.14159265
#endif

/* size in pixels to draw each map cell when drawing the top-down map.
 * Increase to make the map bigger on screen. */
#ifndef ONE_TILE_SIDE
#define ONE_TILE_SIDE 64
#endif

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <X11/keysym.h> // for keysyms like XK_Escape
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <math.h>

#include "../inc/get_next_line.h"
#include "../minilibx-linux/mlx.h"

enum e_colors
{
	COLOR_BLACK = 0x000000,
	COLOR_WHITE = 0xFFFFFF,
	COLOR_RED = 0xFF0000,
	COLOR_GREEN = 0x00FF00,
	COLOR_BLUE = 0x0000FF,
	COLOR_YELLOW = 0xFFFF00,
	COLOR_CYAN = 0x00FFFF,
	COLOR_MAGENTA = 0xFF00FF,
	COLOR_GREY = 0x808080
};

enum e_game_state
{
	STATE_MENU,
	STATE_OPTIONS,
	STATE_PLAYING,
	STATE_PAUSED
};

enum e_texture_index // use this or use e_game_colors?
{
	NORTH_TEXTURE = 0,
	SOUTH_TEXTURE = 1,
	EAST_TEXTURE = 2,
	WEST_TEXTURE = 3
};

/* simple image container */
typedef struct s_img
{
	void	*img_ptr;
	void	*img_pixels_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct	s_map
{
	char	**map;
	char	*map_file;
	char	player_orientation;
	float		player_start_x;
	float		player_start_y;
	int		y_max;

}				t_map;

typedef struct s_ray
{
	double	camera_x; // x-coordinate in camera space
	double	dir_x; // direction of the ray
	double	dir_y; // direction of the ray
	int		map_x;	// current square of the map the ray is in
	int		map_y;	// current square of the map the ray is in
	int		step_x; // direction to step in x and y (either +1 or -1)
	int		step_y; // direction to step in x and y (either +1 or -1)
	double	sidedist_x; // means length of ray from current position to next x or y-side
	double	sidedist_y; // means length of ray from current position to next x or y-side
	double	deltadist_x; // length of ray from one x or y-side to next x or y-side
	double	deltadist_y; // length of ray from one x or y-side to next x or y-side
	double	wall_dist; // perpendicular distance from the ray to the wall
	double	wall_x;    // where exactly the wall was hit
	int		side;			 // was a NS or a EW wall hit?
	int		line_height;   // height of line to draw on screen
	int		draw_start;   // lowest pixel to fill in current stripe
	int		draw_end;     // highest pixel to fill in current stripe
}	t_ray;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x; // whats plane_x? it's a 2D raycaster version of camera plane
	double	plane_y; // whats the difference between dir_y and plane_y? dir_y is the direction the player is facing, plane_y is perpendicular to that direction and defines the field of view
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct	s_game
{
	t_map				map;
	void				*mlx_struct;
	void				*win_struct;
	int					win_w; /* current window width */
	int					win_h; /* current window height */
	t_img				image;
}				t_game;

//parsing.c
void	parse(int ac, char **av);

//free_me_baby.c
void	free_game(t_game *game);

//handle_map.c
void	handle_map(char *map_file, t_game *game);

//map_validation.c
bool	map_is_valid(t_game *game);

// initiate.c
void	initiate_mlx(t_game *game);

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