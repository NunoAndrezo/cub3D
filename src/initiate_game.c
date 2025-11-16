#include "../inc/cub3d.h"

static int	key_press(int keycode, void *param);
static int	mouse_hook(int button, int x, int y, void *param);
static int	expose_hook(void *param);
static void render_menu(t_game *game);
static void	composite_cursor_onto_buffer(t_game *game, char *dst_data, int dst_sl, int dst_pp, int dst_w, int dst_h, int cx, int cy);
static void	blit_cursor_pixels_to_window(t_game *game, int cx, int cy);

void	initiate_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		perror("mlx_init failed");
		exit(1);
	}
	/* create window and store its size in the game struct */
	game->win_w = 1920;
	game->win_h = 1000;
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "Cub3D");
	if (!game->win)
	{
		perror("mlx_new_window failed");
		exit(1);
	}
	(void)game;
	/* register key hooks: KeyPress (2) and KeyRelease (3) to be robust */
	mlx_hook(game->win, 2, 1L<<0, key_press, game);
	mlx_hook(game->win, 3, 1L<<1, key_press, game);
	/* mouse clicks */
	mlx_mouse_hook(game->win, mouse_hook, game);
	/* register expose hook so the menu redraws when needed */
	mlx_expose_hook(game->win, expose_hook, game);
	/* no animation loop: cursor is static */
	//mlx_key_hook(game->win, key_press, &game); this one is an alias of mlx_hook on key up event (3). 
	render_menu(game); // render the menu initially
	mlx_loop(game->mlx);
}

static int	key_press(int keycode, void *param)
{
	t_game *g = (t_game *)param;
	/* Menu navigation when in menu state */
	if (g->state == STATE_MENU)
	{
		if (keycode == 65362) /* Up */
		{
			g->menu_selection = (g->menu_selection + 3 - 1) % 3;
			render_menu(g);
			return (0);
		}
		if (keycode == 65364) /* Down */
		{
			g->menu_selection = (g->menu_selection + 1) % 3;
			render_menu(g);
			return (0);
		}
		if (keycode == 65293) /* Enter */
		{
			if (g->menu_selection == 0)
				g->state = STATE_PLAYING;
			else if (g->menu_selection == 1)
				g->state = STATE_OPTIONS;
			else if (g->menu_selection == 2)
			{
				if (g->menu_image.img_ptr)
					mlx_destroy_image(g->mlx, g->menu_image.img_ptr);
				if (g->win)
					mlx_destroy_window(g->mlx, g->win);
				exit(0);
			}
			return (0);
		}
	}

	/* Global ESC behavior */
	if (keycode == 65307) /* ESC */
	{
		if (g->menu_image.img_ptr)
			mlx_destroy_image(g->mlx, g->menu_image.img_ptr);
		if (g->cursor.img_ptr)
			mlx_destroy_image(g->mlx, g->cursor.img_ptr);
		if (g->win)
			mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	return (0);
}

/* animation removed: cursor is static */

static int	mouse_hook(int button, int x, int y, void *param)
{
	t_game *g = (t_game *)param;
	/* left click */
	if (button == 1 && g->state == STATE_MENU)
	{
		/* buttons are at x~400.., y at 200,260,320 */
		if (x >= 300 && x <= 800)
		{
			if (y >= 190 && y <= 220)
				g->menu_selection = 0;
			else if (y >= 250 && y <= 280)
				g->menu_selection = 1;
			else if (y >= 310 && y <= 340)
				g->menu_selection = 2;
			render_menu(g);
			/* emulate Enter */
			if (g->menu_selection == 0)
				fprintf(stderr, "Menu: START selected (mouse)\n"), g->state = STATE_PLAYING;
			else if (g->menu_selection == 1)
				fprintf(stderr, "Menu: OPTIONS selected (mouse)\n"), g->state = STATE_OPTIONS;
			else if (g->menu_selection == 2)
			{	fprintf(stderr, "Menu: EXIT selected (mouse)\n");
				if (g->menu_image.img_ptr)
					mlx_destroy_image(g->mlx, g->menu_image.img_ptr);
				if (g->cursor.img_ptr)
					mlx_destroy_image(g->mlx, g->cursor.img_ptr);
				if (g->win)
					mlx_destroy_window(g->mlx, g->win);	
				exit(0);
			}
		}
	}
	return (0);
}

static int	expose_hook(void *param)
{
	render_menu((t_game *)param);
	return (0);
}

static void render_menu(t_game *game)
{
	char *game_menu_image_path;

	game_menu_image_path = "assets/textures/game_menu1.xpm";
	/* Clear the window first */
	mlx_clear_window(game->mlx, game->win);
	/* Load XPM menu_image once and cache it on the game struct */
	if (!game->menu_image.img_ptr)
	{
		game->menu_image.path = game_menu_image_path;
		game->menu_image.img_ptr = mlx_xpm_file_to_image(game->mlx, game->menu_image.path, &game->menu_image.w, &game->menu_image.h);
	}
	/* Load cursor menu_image once */
	if (!game->cursor.img_ptr)
	{
		game->cursor.path = "assets/textures/Cursor.xpm";
		game->cursor.img_ptr = mlx_xpm_file_to_image(game->mlx, game->cursor.path, &game->cursor.w, &game->cursor.h);
	}
	if (game->menu_image.img_ptr)
	{
		/* If menu_image matches window size, blit directly */
		if (game->menu_image.w == game->win_w && game->menu_image.h == game->win_h)
		{
			/* create a temporary canvas, copy the background into it and composite cursor (so background pixels stay intact) */
			if (game->cursor.img_ptr)
			{
				int src_bpp, src_sl, src_endian;
				int dst_bpp, dst_sl, dst_endian;
				char *src_data = mlx_get_data_addr(game->menu_image.img_ptr, &src_bpp, &src_sl, &src_endian);
				void *dst_img = mlx_new_image(game->mlx, game->menu_image.w, game->menu_image.h);
				if (dst_img && src_data)
				{
					char *dst_data = mlx_get_data_addr(dst_img, &dst_bpp, &dst_sl, &dst_endian);
					/* copy background rows */
					int rows = game->menu_image.h;
					int copy_stride = (src_sl < dst_sl) ? src_sl : dst_sl;
					for (int y = 0; y < rows; ++y)
					{
						char *srow = src_data + y * src_sl;
						char *drow = dst_data + y * dst_sl;
						memcpy(drow, srow, copy_stride);
					}
					/* composite cursor */
					int base_x = 300;
					int ys[3] = {200, 260, 320};
					int cy = ys[game->menu_selection] - (game->cursor.h / 2);
					int cx = base_x - game->cursor.w - 10;
					composite_cursor_onto_buffer(game, dst_data, dst_sl, dst_bpp / 8, game->menu_image.w, game->menu_image.h, cx, cy);
					mlx_put_image_to_window(game->mlx, game->win, dst_img, 0, 0);
					mlx_destroy_image(game->mlx, dst_img);
					return;
				}
			}
			/* no cursor or temp image failed: fallback to direct put */
			mlx_put_image_to_window(game->mlx, game->win, game->menu_image.img_ptr, 0, 0);
		}
		else
		{
			/* create a temporary menu_image sized to the window and scale source into it (nearest-neighbor) */
			int src_bpp, src_sl, src_endian;
			int dst_bpp, dst_sl, dst_endian;
			char *src_data = mlx_get_data_addr(game->menu_image.img_ptr, &src_bpp, &src_sl, &src_endian);
			void *dst_img = mlx_new_image(game->mlx, game->win_w, game->win_h);
			if (!dst_img)
			{
				/* fallback to direct put if we can't allocate scaled menu_image */
				mlx_put_image_to_window(game->mlx, game->win, game->menu_image.img_ptr, 0, 0);
				return;
			}
			char *dst_data = mlx_get_data_addr(dst_img, &dst_bpp, &dst_sl, &dst_endian);
			if (!src_data || !dst_data)
			{
				mlx_put_image_to_window(game->mlx, game->win, game->menu_image.img_ptr, 0, 0);
				mlx_destroy_image(game->mlx, dst_img);
				return;
			}
			int src_w = game->menu_image.w;
			int src_h = game->menu_image.h;
			int dst_w = game->win_w;
			int dst_h = game->win_h;
			int src_pp = src_bpp / 8;
			int dst_pp = dst_bpp / 8;
			for (int y = 0; y < dst_h; ++y)
			{
				int src_y = (y * src_h) / dst_h;
				char *dst_row = dst_data + y * dst_sl;
				char *src_row = src_data + src_y * src_sl;
				for (int x = 0; x < dst_w; ++x)
				{
					int src_x = (x * src_w) / dst_w;
					char *dst_px = dst_row + x * dst_pp;
					char *src_px = src_row + src_x * src_pp;
					/* copy min(src_pp, dst_pp) bytes (usually 4) */
					int copy_bytes = src_pp < dst_pp ? src_pp : dst_pp;
					for (int b = 0; b < copy_bytes; ++b)
						dst_px[b] = src_px[b];
					/* if dst is 4 bytes and src is 3, set alpha to 0x00 or 0xFF as appropriate */
					if (dst_pp == 4 && src_pp == 3)
						dst_px[3] = 0x00;
				}
			}
			/* composite cursor onto dst_data so transparent pixels don't overwrite background */
			if (game->cursor.img_ptr && game->state == STATE_MENU)
			{
				int base_x = 300;
				int ys[3] = {200, 260, 320};
				int cy = ys[game->menu_selection] - (game->cursor.h / 2);
				int cx = base_x - game->cursor.w - 10;
				composite_cursor_onto_buffer(game, dst_data, dst_sl, dst_pp, dst_w, dst_h, cx, cy);
			}
			mlx_put_image_to_window(game->mlx, game->win, dst_img, 0, 0);
			mlx_destroy_image(game->mlx, dst_img);
		}
	}
	else
	{
		/* If no background menu_image, still draw cursor beside text (if available) */
		if (game->cursor.img_ptr && game->state == STATE_MENU)
		{
			/* no background to composite into: draw cursor pixels directly (skip fully black pixels) */
			int base_x = 300;
			int ys[3] = {200, 260, 320};
				int cy = ys[game->menu_selection] - (game->cursor.h / 2);
				int cx = base_x - game->cursor.w - 10;
			blit_cursor_pixels_to_window(game, cx, cy);
		}
	}
}

/* Composite non-black pixels from cursor image into an existing destination buffer */
static void	composite_cursor_onto_buffer(t_game *game, char *dst_data, int dst_sl, int dst_pp, int dst_w, int dst_h, int cx, int cy)
{
	int src_bpp, src_sl, src_endian;
	char *src = mlx_get_data_addr(game->cursor.img_ptr, &src_bpp, &src_sl, &src_endian);
	if (!src)
		return;
	int src_pp = src_bpp / 8;
	for (int sy = 0; sy < game->cursor.h; ++sy)
	{
		int dy = cy + sy;
		if (dy < 0 || dy >= dst_h)
			continue;
		char *src_row = src + sy * src_sl;
		char *dst_row = dst_data + dy * dst_sl;
		for (int sx = 0; sx < game->cursor.w; ++sx)
		{
			int dx = cx + sx;
			if (dx < 0 || dx >= dst_w)
				continue;
			char *s_px = src_row + sx * src_pp;
			char *d_px = dst_row + dx * dst_pp;
			/* treat fully black (first 3 bytes zero) as transparent */
			int is_transparent = 1;
			for (int c = 0; c < 3 && c < src_pp; ++c)
				if ((unsigned char)s_px[c] != 0)
					is_transparent = 0;
			if (is_transparent)
				continue;
			/* copy pixel bytes */
			int copy = src_pp < dst_pp ? src_pp : dst_pp;
			for (int b = 0; b < copy; ++b)
				d_px[b] = s_px[b];
			if (dst_pp == 4 && src_pp == 3)
				d_px[3] = 0x00;
		}
	}
}

/* Draw cursor pixels directly into the window (used when no background image is present) */
static void	blit_cursor_pixels_to_window(t_game *game, int cx, int cy)
{
	int src_bpp, src_sl, src_endian;
	char *src = mlx_get_data_addr(game->cursor.img_ptr, &src_bpp, &src_sl, &src_endian);
	if (!src)
		return;
	int src_pp = src_bpp / 8;
	for (int sy = 0; sy < game->cursor.h; ++sy)
	{
		for (int sx = 0; sx < game->cursor.w; ++sx)
		{
			char *s_px = src + sy * src_sl + sx * src_pp;
			/* skip fully black pixels */
			int is_transparent = 1;
			for (int c = 0; c < 3 && c < src_pp; ++c)
				if ((unsigned char)s_px[c] != 0)
					is_transparent = 0;
			if (is_transparent)
				continue;
			/* assemble RGB color assuming src_px order B,G,R (common on X11 little-endian) */
			unsigned char b = (src_pp > 0) ? (unsigned char)s_px[0] : 0;
			unsigned char g = (src_pp > 1) ? (unsigned char)s_px[1] : 0;
			unsigned char r = (src_pp > 2) ? (unsigned char)s_px[2] : 0;
			int color = (r << 16) | (g << 8) | b;
			mlx_pixel_put(game->mlx, game->win, cx + sx, cy + sy, color);
		}
	}
}