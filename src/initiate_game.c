#include "../inc/cub3d.h"

static int	key_press(int key_sym, t_game *game);
static int	key_release(int key_sym, t_game *game);

static int	button_x_on_window(void *param);

static int	game_loop(t_game *game);
static int	main_loop(t_game *game);
static void	update_game(t_game *game);
static void	draw_map_to_image(t_game *game, t_img *target);
static void	initiate_player(t_game *game);
static void	draw_player(t_game *game);
static void	change_player_rot(t_game *game);
static void	change_player_mov(t_game *game);
static bool	is_colision(t_game *game, float nx, float ny);
static bool	check_diagonally_strafing(t_game *game);
uint64_t	get_time_in_ms(void);

void	initiate_mlx(t_game *game)
{
	game->mlx_struct = mlx_init(); // Create a structure to hold minilibx info
	if (!game->mlx_struct)
	{
		perror("mlx_init failed");
		free_game(game);
		exit(1);
	}
	game->win_w = WWIDTH;
	game->win_h = WHEIGHT;
	if (WWIDTH > 1920 || WWIDTH <= 0)
		game->win_w = 1920;
	if (WHEIGHT > 1000 || WHEIGHT <= 0)
		game->win_h = 1000;
	game->win_struct = mlx_new_window(game->mlx_struct, game->win_w, game->win_h, "Cub3D"); // Create a structure to hold window info
	if (!game->win_struct)
	{
		perror("mlx_new_window failed");
		free_game(game);
		exit(1);
	}
	game->max_distance = sqrt((game->win_w * ONE_TILE_SIDE) * (game->win_w * ONE_TILE_SIDE) + (game->win_h * ONE_TILE_SIDE) * (game->win_h * ONE_TILE_SIDE));
	game->start_time = get_time_in_ms();
	initiate_player(game);
	ft_bzero(&game->ray, sizeof(t_ray));
	mlx_hook(game->win_struct, 2, 1L<<0, key_press, game); // key press. 1L<<0 mask, means KeyPress. 2 event means KeyPress
	// could also use mlx_key_hook(game->win_struct, key_press, game);
	mlx_hook(game->win_struct, 3, 1L<<1, key_release, game); // key release. 1L<<1 mask, means KeyRelease. 3 event means KeyRelease
	mlx_hook(game->win_struct, 17, 1L<<0, button_x_on_window, game); // window close button (X) pressed - 17 event is DestroyNotify
	//mlx_hook(game->win_struct, 3, 1L<<1, key_press, game); // key release. 1L<<1 mask, means KeyRelease. 3 event means KeyRelease
	
	// we use this image buffer to draw the game state before putting it to the window, this way we avoid flickering since it's drawn off-screen first
	game->image.width = game->win_w;
	game->image.height = game->win_h;
	game->image.img_ptr = mlx_new_image(game->mlx_struct, game->win_w, game->win_h); // create the image buffer to draw on
	game->image.bits_per_pixel = ONE_TILE_SIDE;
	game->image.img_pixels_ptr = mlx_get_data_addr(game->image.img_ptr, &game->image.bits_per_pixel, &game->image.line_length, &game->image.endian);
	//end of image buffer setup

	/* create a background image and render the static map into it once */
	game->bg_image.width = game->win_w;
	game->bg_image.height = game->win_h;
	game->bg_image.img_ptr = mlx_new_image(game->mlx_struct, game->win_w, game->win_h);
	game->bg_image.bits_per_pixel = ONE_TILE_SIDE;
	game->bg_image.img_pixels_ptr = mlx_get_data_addr(game->bg_image.img_ptr, &game->bg_image.bits_per_pixel, &game->bg_image.line_length, &game->bg_image.endian);

	/* draw map once into background */
	draw_map_to_image(game, &game->bg_image);

	mlx_loop_hook(game->mlx_struct, main_loop, game); // set the loop hook to update the game frame
	mlx_loop(game->mlx_struct); // function that keeps the window open and listens for events.
	//events: key presses, mouse movements, window close, etc.
}

static int game_loop(t_game *game)
{
	// Here we would update the game state, e.g. move player based on input
	// So what is missing? I need to handle rotation of the player too
	/*
	 * Fast per-frame background restore:
	 * We render the static top-down map once into `game->bg_image` at startup
	 * (see `draw_map_to_image`) and then copy that full image into the
	 * frame buffer each frame before drawing dynamic items (player, rays).
	 *
	 * Rationale:
	 * - A single block copy (`ft_memcpy`) of the pixel memory is far faster
	 *   than redrawing every static pixel or doing a per-pixel clear loop.
	 * - We copy `line_length * height` bytes, which matches the layout
	 *   returned by `mlx_get_data_addr` (`img_pixels_ptr`). This preserves
	 *   the exact row stride and pixel format used by the MLX image.
	 * - We use our fast `ft_memcpy` implementation (word-sized copies) to
	 *   avoid the system `memcpy` while keeping high performance.
	 *
	 * Notes:
	 * - If you later switch to partial redraws or don't fill every pixel,
	 *   you may need to clear regions explicitly. Currently the background
	 *   copy ensures every pixel is initialized each frame.
	 */
	size_t row_bytes;

	row_bytes = (size_t)game->image.line_length * (size_t)game->image.height;
	if (game->bg_image.img_pixels_ptr && game->image.img_pixels_ptr)
		ft_memcpy(game->image.img_pixels_ptr, game->bg_image.img_pixels_ptr, row_bytes);

	/* draw dynamic elements on top of background */
	draw_player(game);
	lets_see_them_rays(game);
	mlx_put_image_to_window(game->mlx_struct, game->win_struct, game->image.img_ptr, 0, 0);
	return (0);
}

uint64_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main_loop(t_game *game)
{
	uint64_t		current_time;
	uint64_t		elapsed;
	uint64_t		accu;

	// reduce accumulator to ~2ms for ~500Hz updates
	accu = 0;
	current_time = get_time_in_ms();
	elapsed = current_time - game->start_time;
	game->start_time = current_time;
	game->delta_time = elapsed;
	accu += elapsed;
	// Update game state at fixed intervals (~16 ms => ~60 updates/sec)
	while (accu >= 16)
	{
		update_game(game);
		accu -= 16;
	}
	game_loop(game);
	return (0);
}

static void update_game(t_game *game)
{
	// Here we would update the game state, e.g. move player based on input
	// So what is missing? I need to handle rotation of the player too
	change_player_rot(game);
	change_player_mov(game);
}


static void	initiate_player(t_game *game)
{
	ft_bzero(&game->player, sizeof(t_player));
	game->player.pos_x = game->map.player_start_x + 0.5; // center of the tile
	game->player.pos_y = game->map.player_start_y + 0.5; // center of the tile
	game->player.dir = game->map.player_orientation;
	//game->player.move_speed = 5; // pixels per frame
	game->player.move_speed = (float)PLAYER_MOV_SPEED;
	if (game->player.dir == 'N')
	{
		game->player.player_angle = 270.0f; // degrees
	}
	else if (game->player.dir == 'S')
	{
		game->player.player_angle = 90.0f; // degrees
	}
	else if (game->player.dir == 'E')
	{
		game->player.player_angle = 0.0f; // degrees
	}
	else if (game->player.dir == 'W')
	{
		game->player.player_angle = 180.0f; // degrees
	}
	/* store deltas as unit vector using degrees -> radians conversion */
	game->player.player_delta_x = -cosf(deg_to_rad(game->player.player_angle));
	game->player.player_delta_y = -sinf(deg_to_rad(game->player.player_angle));
	/* defaults for rendering/config that moved into player/ray structs */
	game->player.fov_degrees = 45.0f;
	/* default to auto (0) so raycasting uses image width unless overridden */
	game->ray.num_rays = 0;
	game->ray.debug_rays = false;
}

// draw_game wrapper removed — use draw_map_to_image when needed and background cache for per-frame rendering

static void	draw_map_to_image(t_game *game, t_img *target)
{
	int	tile_y;
	int	tile_x;
	int world_x;
	int world_y;
	int	color;

	(void)target; /* my_store_pixel_in_image uses target pointer directly */
	tile_y = 0;
	int xrow;
	/* draw each map cell as a ONE_TILE_SIDE x ONE_TILE_SIDE square so the map is larger on screen */
	while (game->map.map[tile_y])
	{
		tile_x = 0;
		xrow = ft_strlen(game->map.map[tile_y]);
		while (tile_x < xrow)
		{
			world_y = tile_y * ONE_TILE_SIDE;
			world_x = tile_x * ONE_TILE_SIDE;
			if (game->map.map[tile_y][tile_x] == '1')
				color = COLOR_WHITE; // wall
			else if (game->map.map[tile_y][tile_x] == ' ')
				color = COLOR_GREY; // empty space
			else
				color = COLOR_BLACK; // other (e.g. sprites)
			// draw the square for this map cell
			for (int y = 0; y < ONE_TILE_SIDE; y++)
				for (int x = 0; x < ONE_TILE_SIDE; x++)
					my_store_pixel_in_image(target, world_x + x, world_y + y, color);
			// draw cell borders
			for (int i = 0; i < ONE_TILE_SIDE; i++)
			{
				my_store_pixel_in_image(target, world_x + i, world_y, COLOR_GREY); // top
				my_store_pixel_in_image(target, world_x + i, world_y + ONE_TILE_SIDE - 1, COLOR_GREY); // bottom
				my_store_pixel_in_image(target, world_x, world_y + i, COLOR_GREY); // left
				my_store_pixel_in_image(target, world_x + ONE_TILE_SIDE - 1, world_y + i, COLOR_GREY); // right
			}
			tile_x++;
		}
		tile_y++;
	}
}

// Detailed explanation:
// This function calculates the memory offset for a pixel at coordinates (x, y) in the image.
// it calculates the offset in the image's pixel game array using the formula:
// offset = (line_length * y) + (x * (bits_per_pixel / 8))
// Here, line_length is the number of bytes in a single row of pixels, y is the row number, x is the column number, and bits_per_pixel / 8 converts bits to bytes.
// Finally, it stores the color value at the calculated offset by casting the offset pointer to an unsigned int pointer and dereferencing it to set the color
void	my_store_pixel_in_image(t_img *image, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ; // out of bounds
	offset = (image->line_length * y) + (x * (image->bits_per_pixel / 8));
	*(unsigned int *)(image->img_pixels_ptr + offset) = color;
}

// keysymbolics are better than keycodes for portability, because keycodes can vary between systems since keycode is hardware specific
// whereas keysymol is more abstract and represents the actual character or function of the key
static int	key_press(int key_sym, t_game *game)
{
	//need to change this whole function, because its only going to handle bools for movement and rotation, while the main loop will update the position based on those bools
	//and that will allow for smoother movement when multiple keys are pressed

	/* Global ESC behavior */
	if (key_sym == XK_Escape) // ESC key code == 65307, key_sym == XK_Escape == 0xff1b
	{
		free_game(game);
		exit(0);
	}
	if (key_sym == XK_w)
		game->player.player_mov_forward = true;
	if (key_sym == XK_a)
		game->player.player_mov_left = true;
	if (key_sym == XK_s)
		game->player.player_mov_backward = true;
	if (key_sym == XK_d)
		game->player.player_mov_right = true;
	if (key_sym == XK_Left)
		game->player.player_rot_left = true;
	if (key_sym == XK_Right)
		game->player.player_rot_right = true;
	return (0);
}

static int	key_release(int key_sym, t_game *game)
{
	// On key release, we just set the movement/rotation flags to false
	if (key_sym == XK_w)
		game->player.player_mov_forward = false;
	if (key_sym == XK_a)
		game->player.player_mov_left = false;
	if (key_sym == XK_s)
		game->player.player_mov_backward = false;
	if (key_sym == XK_d)
		game->player.player_mov_right = false;
	if (key_sym == XK_Left)
		game->player.player_rot_left = false;
	if (key_sym == XK_Right)
		game->player.player_rot_right = false;
	return (0);
}

static void draw_player(t_game *game)
{
	int	size;
	int	player_pixel_x;
	int	player_pixel_y;
	int	y;
	int	x;

	size = 3; // half-size of player square
	player_pixel_x = (int)(game->player.pos_x * ONE_TILE_SIDE);
	player_pixel_y = (int)(game->player.pos_y * ONE_TILE_SIDE);
	y = -size;
	x = -size;
	// lets draw my angle line
	for (int i = 0; i < 15; i++)
	{
		int line_x = player_pixel_x + (int)(cosf(deg_to_rad(game->player.player_angle)) * i);
		int line_y = player_pixel_y + (int)(sinf(deg_to_rad(game->player.player_angle)) * i);
		my_store_pixel_in_image(&game->image, line_x, line_y, COLOR_YELLOW);
	}
	// now draw the player as a square
	while (y <= size)
	{
		x = -size;
		while (x <= size)
		{
			my_store_pixel_in_image(&game->image, player_pixel_x + x, player_pixel_y + y, COLOR_YELLOW);
			x++;
		}
		y++;
	}
}

static void change_player_rot(t_game *game)
{
	/* Compute rotation delta in DEGREES. The old code used a radian delta
	   of (PLAYER_MOV_SPEED / 50.0f). To preserve the previous angular
	   speed after switching to degrees, convert that radian delta to
	   degrees using `rad_to_deg`.
	*/
	float rot_delta_deg = rad_to_deg((float)PLAYER_MOV_SPEED / 50.0f);
	if (game->player.player_rot_left)
	{
		game->player.player_angle -= rot_delta_deg;
		if (game->player.player_angle < 0.0f)
			game->player.player_angle += 360.0f;
		game->player.player_delta_x = -cosf(deg_to_rad(game->player.player_angle));
		game->player.player_delta_y = -sinf(deg_to_rad(game->player.player_angle));
	}
	if (game->player.player_rot_right)
	{
		game->player.player_angle += rot_delta_deg; /* degrees */
		if (game->player.player_angle > 360.0f)
			game->player.player_angle -= 360.0f;
		game->player.player_delta_x = -cosf(deg_to_rad(game->player.player_angle));
		game->player.player_delta_y = -sinf(deg_to_rad(game->player.player_angle));
	}
}

static void change_player_mov(t_game *game)
{
	float	nx;
	float	ny;
	bool	strafing_diagonally;

	nx = game->player.pos_x;
	ny = game->player.pos_y;
	strafing_diagonally = check_diagonally_strafing(game);
	if (strafing_diagonally)
		game->player.move_speed = (float)PLAYER_MOV_SPEED / 1.4f; // reduce speed when moving diagonally
	else
		game->player.move_speed = (float)PLAYER_MOV_SPEED; // normal speed
	// Move in fractional tile units
	if (game->player.player_mov_left)
	{
		ny += game->player.player_delta_x * (game->player.move_speed / (float)ONE_TILE_SIDE);
		nx -= game->player.player_delta_y * (game->player.move_speed / (float)ONE_TILE_SIDE); // should be a minus? because its negative in the perpendicular direction? the answer is no, because player_delta_y is already negative when facing up. since y axis is inverted
	}
	else if (game->player.player_mov_right)
	{
		ny -= game->player.player_delta_x * (game->player.move_speed / (float)ONE_TILE_SIDE);
		nx += game->player.player_delta_y * (game->player.move_speed / (float)ONE_TILE_SIDE);
	}
	if (game->player.player_mov_forward)
	{
		nx -= game->player.player_delta_x * (game->player.move_speed / (float)ONE_TILE_SIDE);
		ny -= game->player.player_delta_y * (game->player.move_speed / (float)ONE_TILE_SIDE);
	}
	else if (game->player.player_mov_backward)
	{
		nx += game->player.player_delta_x * (game->player.move_speed / (float)ONE_TILE_SIDE);
		ny += game->player.player_delta_y * (game->player.move_speed / (float)ONE_TILE_SIDE);
	}
	// Check if new position is walkable
	if (is_colision(game, nx, ny) == false)
	{
		game->player.pos_x = nx;
		game->player.pos_y = ny;
	}
}

static bool check_diagonally_strafing(t_game *game)
{
	if (game->player.player_mov_forward && game->player.player_mov_left)
		return (true);
	if (game->player.player_mov_backward && game->player.player_mov_left)
		return (true);
	if (game->player.player_mov_forward && game->player.player_mov_right)
		return (true);
	if (game->player.player_mov_backward && game->player.player_mov_right)
		return (true);
	return (false);
}

static bool is_colision(t_game *game, float nx, float ny)
{
	// Check if new position is walkable
	if (ny >= 0 && (int)ny < game->map.y_max &&
		nx >= 0 && (int)nx < (int)ft_strlen(game->map.map[(int)ny]) &&
		game->map.map[(int)(ny)][(int)(nx)] != '1' && game->map.map[(int)(ny)][(int)(nx)] != ' ')
	{
		return (false); // no collision
	}
	return (true); // collision
}

static int	button_x_on_window(void *param)
{
	t_game *g = (t_game *)param;
	free_game(g);
	exit(0);
	return (0);
}
