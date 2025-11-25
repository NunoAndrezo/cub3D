#include "../inc/cub3d.h"

static int	key_press(int key_sym, t_game *game);
static int	button_x_on_window(void *param);
static void	draw_game(t_game *game); // forward declaration
static void	redraw_game(t_game *game, int key_sym); // forward declaration
static void	my_store_pixel_in_image(t_img *image, int x, int y, int color);

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

static void	draw_game(t_game *game)
{
	int		j;
	int		i;

	j = 0;
	/* draw each map cell as a TILE_SIZE x TILE_SIZE square so the map is larger on screen */
	while (game->map.map[j])
	{
		i = 0;
		while (game->map.map[j][i])
		{
			int base_x = i * TILE_SIZE;
			int base_y = j * TILE_SIZE;
			int color = (game->map.map[j][i] == '1') ? COLOR_WHITE : COLOR_BLACK;
			for (int yy = 0; yy < TILE_SIZE; ++yy)
			{
				for (int xx = 0; xx < TILE_SIZE; ++xx)
				{
					my_store_pixel_in_image(&game->image, base_x + xx, base_y + yy, color);
				}
			}
			i++;
		}
		j++;
	}
//	mlx_put_image_to_window(game->mlx_struct, game->win_struct, game->image.img_ptr, 0, 0); // put the image buffer to the window
	/* draw player as a filled TILE_SIZE square centered on player cell */
	float	px;
	float	py;
	px = game->map.player_start_x;
	py = game->map.player_start_y;
	px *= TILE_SIZE;
	py *= TILE_SIZE;
	float xx = 0;
	float yy = 0;
	while (yy < TILE_SIZE)
	{
		while (xx < TILE_SIZE)
		{
			if ( px + xx >= 0 && px + xx < game->win_w && py + yy >= 0 && py + yy < game->win_h )
			{
					if (game->map.map[(int)(py / TILE_SIZE)][(int)(px / TILE_SIZE)] != '1') // only draw player if not inside a wall
						my_store_pixel_in_image(&game->image, px + xx, py + yy, PLAYER_COLOR);
			}
			xx++;
		}
		xx = 0;
		yy++;
	}
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
	// For simplicity, we will just clear the window and redraw the game state
	bool moved;

	moved = false;
	if (key_sym == XK_w)
	{
		// move player forward
		if (game->map.map[(int)(game->map.player_start_y - 1)][(int)(game->map.player_start_x)] != '1') // only move if not into a wall
		{
			game->map.player_start_y -= 1;
			mlx_clear_window(game->mlx_struct, game->win_struct);
			moved = true;
		}
	}
	else if (key_sym == XK_s)
	{
		// move player backward
		if (game->map.map[(int)(game->map.player_start_y + 1)][(int)(game->map.player_start_x)] != '1') // only move if not into a wall
		{
			game->map.player_start_y += 1;
			mlx_clear_window(game->mlx_struct, game->win_struct);
			moved = true;
		}
	}
	else if (key_sym == XK_a)
	{
		// move player left
		if (game->map.map[(int)(game->map.player_start_y)][(int)(game->map.player_start_x - 1)] != '1') // only move if not into a wall
		{
			game->map.player_start_x -= 1;
			mlx_clear_window(game->mlx_struct, game->win_struct);
			moved = true;
		}
	}
	else if (key_sym == XK_d)
	{
		// move player right
		if (game->map.map[(int)(game->map.player_start_y)][(int)(game->map.player_start_x + 1)] != '1') // only move if not into a wall
		{
			game->map.player_start_x += 1;
			mlx_clear_window(game->mlx_struct, game->win_struct);
			moved = true;
		}
	}
	if (moved)
		draw_game(game);
}

static int	button_x_on_window(void *param)
{
	t_game *g = (t_game *)param;
	free_game(g);
	exit(0);
	return (0);
}
