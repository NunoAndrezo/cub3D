#ifndef CUB3D_H
#define CUB3D_H

#ifndef WWIDTH
#define WWIDTH 1920
#endif
#ifndef WHEIGHT
#define WHEIGHT 1000
#endif

#ifndef PI_VALUE
#define PI_VALUE 3.14159265
#endif

#ifndef PLAYER_MOV_SPEED
#define PLAYER_MOV_SPEED 1
#endif

/* size in pixels to draw each map cell when drawing the top-down map.
 * Increase to make the map bigger on screen. */
#ifndef ONE_TILE_SIDE
#define ONE_TILE_SIDE 16
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
#include <errno.h>
#include <sys/time.h>
#include <stdint.h>

#include "../inc/get_next_line.h"
#include "../minilibx-linux/mlx.h"

enum e_colors
{
	COLOR_BLACK = 0x000000,
	COLOR_BLUE = 0x0000FF,
	COLOR_BROWN = 0xA52A2A,
	COLOR_CYAN = 0x00FFFF,
	COLOR_DARK_GREY = 0x404040,
	COLOR_GREEN = 0x00FF00,
	COLOR_GREY = 0x808080,
	COLOR_LIGHT_GREY = 0xC0C0C0,
	COLOR_MAGENTA = 0xFF00FF,
	COLOR_ORANGE = 0xFFA500,
	COLOR_PINK = 0xFFC0CB,
	COLOR_RED = 0xFF0000,
	COLOR_WHITE = 0xFFFFFF,
	COLOR_YELLOW = 0xFFFF00,
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
	int		y_start;
	int		x_max;
}				t_map;

typedef struct s_ray
{
	float	angle;        // radius angle (rad)
	float	ray_x;        // current position X (tile units)
	float	ray_y;        // current position Y (tile units)
	float	x_step;       // increment in X
	float	y_step;       // increment in Y
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	distance;     // distance till the wall
	int		hit_side;     // 0 = vertical | 1 = horizontal
	float	final_distance;
	/* per-ray configuration */
	int		num_rays; /* 0 = auto (image width) */
	bool	debug_rays; /* draw debug colors for hits */

}	t_ray;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	float	move_speed; /* movement speed in pixels per frame */
	float	player_delta_x; /* movement delta in x direction per frame */
	float	player_delta_y; /* movement delta in y direction per frame */
	float	player_angle; /* player viewing angle in degrees */
	float	fov_degrees; /* field of view in degrees */
	bool	player_mov_forward;
	bool	player_mov_backward;
	bool	player_mov_left;
	bool	player_mov_right;
	bool	player_rot_left;
	bool	player_rot_right;
}	t_player;

typedef struct s_texture
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color[3];
	int		ceiling_color[3];
}	t_texture;

typedef struct	s_game
{
	t_map				map;
	void				*mlx_struct;
	void				*win_struct;
	int					win_w; /* current window width */
	int					win_h; /* current window height */
	t_img				image;
	/* background image contains the static map rendered once to speed up per-frame draws */
	t_img				bg_image;
	/* rendering config moved into player/ray structs */
	t_player			player;
	float				max_distance;
	uint64_t			start_time;
	uint64_t			delta_time;
	float				final_distance;
	t_ray				ray;
	t_texture			textures;
	bool				texture_w;
	bool				texture_s;
	bool				texture_e;
	bool				texture_n;
	bool				color_f;
	bool				color_c;
}				t_game;

//parsing.c
void	parse(int ac, char **av);

//free_me_baby.c
void	free_game(t_game *game);

//handle_map.c
void	handle_map(char *map_file, t_game *game);

//map_validation.c
bool	last_map_adjustments(t_game *game);
bool	map_is_valid(t_game *game);

// initiate.c
void	initiate_mlx(t_game *game);

//setup_signals.c
void	setup_signals(void);


//ft_bzero.c
void	ft_bzero(void *s, size_t n);

// my_math.c
float	deg_to_rad(float angle_in_degrees);
float	rad_to_deg(float angle_in_radians);

//ft_calloc.c
void	*ft_calloc(size_t count, size_t size);

//utils.c
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_char(const char *s, char c);
char	*ft_strcpy(char *dst, const char *src);

//flood_fill.c
bool	flood_fill(t_game *game);

//raycasting.c
void	lets_see_them_rays(t_game *game);

void	my_store_pixel_in_image(t_img *image, int x, int y, int color);
//int		my_clear_image(t_game *game);

//ft_memcpy.c
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memcpy_normal(void *dest, const void *src, size_t n);

//drawing_3d_game.c
void	draw_3Dgame(t_game *game, float angle, float best_dist, int hit_side, 
					int column_index);
//ft_split.c
char	**ft_split(char const *s, char c);

//ft_atoi.c
int		ft_atoi(const char *str);

//ft_strncmp.c
int		ft_strncmp(const char *str1, const char *str2, size_t n);

#endif