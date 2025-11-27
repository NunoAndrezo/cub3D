#include "../inc/cub3d.h"

static int	key_press(int key_sym, t_game *game);
static int	button_x_on_window(void *param);
static void	draw_game(t_game *game); // forward declaration
static void	redraw_game(t_game *game, int key_sym); // forward declaration
static void	my_store_pixel_in_image(t_img *image, int x, int y, int color);
static void draw_player(t_game *game);
static void initiate_player(t_game *game);


void	initiate_mlx(t_game *game)
{
	game->mlx_struct = mlx_init(); // Create a structure to hold minilibx info
	if (!game->mlx_struct)
	{
		perror("mlx_init failed");
		// we need a clean exit function here
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
		// we need a clean exit function here
		exit(1);
	}
	initiate_player(game);
	ft_bzero(&game->ray, sizeof(t_ray));
	mlx_hook(game->win_struct, 2, 1L<<0, key_press, game); // key press. 1L<<0 mask, means KeyPress. 2 event means KeyPress
	// could also use mlx_key_hook(game->win_struct, key_press, game);
	mlx_hook(game->win_struct, 17, 1L<<0, button_x_on_window, game); // window close button (X) pressed - 17 event is DestroyNotify
	//mlx_hook(game->win_struct, 3, 1L<<1, key_press, game); // key release. 1L<<1 mask, means KeyRelease. 3 event means KeyRelease
	
	// we use this image buffer to draw the game state before putting it to the window, this way we avoid flickering since it's drawn off-screen first
	game->image.width = game->win_w;
	game->image.height = game->win_h;
	game->image.img_ptr = mlx_new_image(game->mlx_struct, game->win_w, game->win_h); // create the image buffer to draw on
	game->image.bits_per_pixel = 32; // assuming 32 bits per pixel
	game->image.img_pixels_ptr = mlx_get_data_addr(game->image.img_ptr, &game->image.bits_per_pixel, &game->image.line_length, &game->image.endian);
	//end of image buffer setup

	draw_game(game); // draw the initial game state
	mlx_loop(game->mlx_struct); // function that keeps the window open and listens for events.
	//events: key presses, mouse movements, window close, etc.
}

static void	initiate_player(t_game *game)
{
	game->player.pos_x = game->map.player_start_x + 0.5; // center of the tile
	game->player.pos_y = game->map.player_start_y + 0.5; // center of the tile
	game->player.has_moved = 0;
	game->player.move_x = 0;
	game->player.move_y = 0;
	game->player.rotate = 0;
	game->player.dir = game->map.player_orientation;
	if (game->player.dir == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (game->player.dir == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
	else if (game->player.dir == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (game->player.dir == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
}

static void	draw_game(t_game *game)
{
	int	tile_y;
	int	tile_x;
	int world_x;
	int world_y;
	int	color;

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
			else
				color = COLOR_BLACK; // empty space
			// draw the square for this map cell
			for (int y = 0; y < ONE_TILE_SIDE; y++)
				for (int x = 0; x < ONE_TILE_SIDE; x++)
					my_store_pixel_in_image(&game->image, world_x + x, world_y + y, color);
			for (int i = 0; i < ONE_TILE_SIDE; i++)
			{
				my_store_pixel_in_image(&game->image, world_x + i, world_y, COLOR_GREY); // top
				my_store_pixel_in_image(&game->image, world_x + i, world_y + ONE_TILE_SIDE - 1, COLOR_GREY); // bottom
				my_store_pixel_in_image(&game->image, world_x, world_y + i, COLOR_GREY); // left
				my_store_pixel_in_image(&game->image, world_x + ONE_TILE_SIDE - 1, world_y + i, COLOR_GREY); // right
			}
			tile_x++;
		}
		tile_y++;
	}
//	mlx_put_image_to_window(game->mlx_struct, game->win_struct, game->image.img_ptr, 0, 0); // put the image buffer to the window
	/* draw player as a filled ONE_TILE_SIDE square centered on player cell */
	draw_player(game);
	mlx_put_image_to_window(game->mlx_struct, game->win_struct, game->image.img_ptr, 0, 0);
}

// Detailed explanation:
// This function calculates the memory offset for a pixel at coordinates (x, y) in the image.
// it calculates the offset in the image's pixel data array using the formula:
// offset = (line_length * y) + (x * (bits_per_pixel / 8))
// Here, line_length is the number of bytes in a single row of pixels, y is the row number, x is the column number, and bits_per_pixel / 8 converts bits to bytes.
// Finally, it stores the color value at the calculated offset by casting the offset pointer to an unsigned int pointer and dereferencing it to set the color
static void	my_store_pixel_in_image(t_img *image, int x, int y, int color)
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
	/* Global ESC behavior */
	if (key_sym == XK_Escape) // ESC key code == 65307, key_sym == XK_Escape == 0xff1b
	{
		free_game(game);
		exit(0);
	}
	if (key_sym == XK_w || key_sym == XK_a || key_sym == XK_s || key_sym == XK_d)
		redraw_game(game, key_sym);
	return (0);
}

static void	redraw_game(t_game *game, int key_sym)
{
	float	nx = game->player.pos_x;
	float	ny = game->player.pos_y;

	// Move in fractional tile units
	if (key_sym == XK_w)
		ny -= 0.1f;
	else if (key_sym == XK_s)
		ny += 0.1f;
	else if (key_sym == XK_a)
		nx -= 0.1f;
	else if (key_sym == XK_d)
		nx += 0.1f;

	// Check if new position is walkable
	if (ny >= 0 && (int)ny < game->map.y_max &&
		nx >= 0 && (int)nx < (int)ft_strlen(game->map.map[(int)ny]) &&
		game->map.map[(int)(ny)][(int)(nx)] != '1')
	{
		game->player.pos_x = nx;
		game->player.pos_y = ny;
		mlx_clear_window(game->mlx_struct, game->win_struct);
		draw_game(game);
	}
}

static void draw_player(t_game *game)
{
	int	size;
	int player_pixel_x;
	int player_pixel_y;

	size = 3; // half-size of player square
	player_pixel_x = (int)(game->player.pos_x * ONE_TILE_SIDE);
	player_pixel_y = (int)(game->player.pos_y * ONE_TILE_SIDE);

	for (int y = -size; y < size; y++)
		for (int x = -size; x < size; x++)
			my_store_pixel_in_image(&game->image, player_pixel_x + x, player_pixel_y + y, COLOR_YELLOW);
}



static int	button_x_on_window(void *param)
{
	t_game *g = (t_game *)param;
	free_game(g);
	exit(0);
	return (0);
}
