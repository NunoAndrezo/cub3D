#include "../inc/cub3d.h"
#include <math.h>  // for tanf, sqrtf, fabsf

static void draw_rays(t_game *game, float ray_x, float ray_y, int hit_side);
static void cast_single_ray_two_pass(t_game *game, float angle);

void lets_see_them_rays(t_game *game)
{
	/* Cast many rays across the player's FOV.
	 * We store `player_angle` in DEGREES; compute per-ray angles in degrees,
	 * then convert to radians when calling the ray cast function (which
	 * uses trig functions expecting radians).
	 */
	int num_rays = game->ray.num_rays;
	if (num_rays <= 0)
	{
		/* Default: don't cast more rays than necessary. Use the window
		 * width if smaller than the target, otherwise cap to a modest
		 * default (200) to reduce CPU/GPU work on large windows.
		 */
		int target = 200; /* sensible default ray count */
		num_rays = (game->image.width < target) ? game->image.width : target;
	}

	float start_angle_deg = game->player.player_angle - (game->player.fov_degrees / 2.0f);
	float angle_step_deg = game->player.fov_degrees / (float)num_rays;

	for (int i = 0; i < num_rays; ++i)
	{
		float a_deg = start_angle_deg + (i + 0.5f) * angle_step_deg; /* degrees */
		while (a_deg < 0.0f) a_deg += 360.0f;
		while (a_deg >= 360.0f) a_deg -= 360.0f;
		float a_rad = deg_to_rad(a_deg);
		cast_single_ray_two_pass(game, a_rad);
	}
}

/*
 * Simpler two-pass raycasting: compute horizontal and vertical intersections
 * in tile coordinates (player.pos_x/pos_y are in tile units), then pick
 * the nearer hit. hit_side: 0 = vertical, 1 = horizontal, -1 = none
 */
static void cast_single_ray_two_pass(t_game *game, float angle)
{
	float dirX = cosf(angle);
	float dirY = sinf(angle);

	float px = (float)game->player.pos_x;
	float py = (float)game->player.pos_y;

	float maxd = game->max_distance / (float)ONE_TILE_SIDE; /* convert max distance to tile units */

	float best_dist = 1e30f;
	float hitX = px, hitY = py;
	int hit_side = -1; /* 0 = vertical, 1 = horizontal */

	/* --- HORIZONTAL intersections --- */
	if (fabsf(dirY) > 1e-9f)
	{
		float y_intercept = (dirY > 0.0f) ? floorf(py) + 1.0f : floorf(py);
		float x_intercept = px + (y_intercept - py) * (dirX / dirY);
		float y_step = (dirY > 0.0f) ? 1.0f : -1.0f;
		float x_step = y_step * (dirX / dirY);

		float cur_x = x_intercept;
		float cur_y = y_intercept;
		while (1)
		{
			int mapY = (int)(cur_y + (dirY < 0.0f ? -1 : 0)); /* if ray going up, check tile above the horizontal line */
			int mapX = (int)floorf(cur_x);
			if (mapY < 0 || mapY >= game->map.y_max)
				break;
			if (mapX < 0 || mapX >= (int)ft_strlen(game->map.map[mapY]))
				break;
			if (game->map.map[mapY][mapX] == '1')
			{
				float dx = cur_x - px;
				float dyv = cur_y - py;
				float dist = sqrtf(dx*dx + dyv*dyv);
				if (dist < best_dist)
				{
					best_dist = dist;
					hitX = cur_x;
					hitY = cur_y;
					hit_side = 1;
				}
				break;
			}
			/* advance to next horizontal gridline */
			cur_x += x_step;
			cur_y += y_step;
			if (sqrtf((cur_x-px)*(cur_x-px) + (cur_y-py)*(cur_y-py)) > maxd)
				break;
		}
	}

	/* --- VERTICAL intersections --- */
	if (fabsf(dirX) > 1e-9f)
	{
		float x_intercept = (dirX > 0.0f) ? floorf(px) + 1.0f : floorf(px);
		float y_intercept = py + (x_intercept - px) * (dirY / dirX);
		float x_step = (dirX > 0.0f) ? 1.0f : -1.0f;
		float y_step = x_step * (dirY / dirX);

		float cur_x = x_intercept;
		float cur_y = y_intercept;
		while (1)
		{
			int mapX = (int)(cur_x + (dirX < 0.0f ? -1 : 0)); /* if ray going left, check tile left of vertical line */
			int mapY = (int)floorf(cur_y);
			if (mapY < 0 || mapY >= game->map.y_max)
				break;
			if (mapX < 0 || mapX >= (int)ft_strlen(game->map.map[mapY]))
				break;
			if (game->map.map[mapY][mapX] == '1')
			{
				float dxv = cur_x - px;
				float dy = cur_y - py;
				float dist = sqrtf(dxv*dxv + dy*dy);
				if (dist < best_dist)
				{
					best_dist = dist;
					hitX = cur_x;
					hitY = cur_y;
					hit_side = 0;
				}
				break;
			}
			/* advance to next vertical gridline */
			cur_x += x_step;
			cur_y += y_step;
			if (sqrtf((cur_x-px)*(cur_x-px) + (cur_y-py)*(cur_y-py)) > maxd)
				break;
		}
	}

	/* draw the chosen ray/hit */
	draw_rays(game, hitX, hitY, hit_side);
}

static void draw_rays(t_game *game, float ray_x, float ray_y, int hit_side)
{
	// Convert tile coordinates to pixels once
	int player_pixel_x = (int)(game->player.pos_x * ONE_TILE_SIDE);
	int player_pixel_y = (int)(game->player.pos_y * ONE_TILE_SIDE);
	int ray_pixel_x = (int)(ray_x * ONE_TILE_SIDE);
	int ray_pixel_y = (int)(ray_y * ONE_TILE_SIDE);

	int dx = ray_pixel_x - player_pixel_x;
	int dy = ray_pixel_y - player_pixel_y;
	int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
	if (steps == 0) return;

	float x_inc = dx / (float)steps;
	float y_inc = dy / (float)steps;
	float x = player_pixel_x;
	float y = player_pixel_y;

	/* draw the chosen ray line in yellow */
	for (int i = 0; i <= steps; i++)
	{
		if (x >= 0 && x < game->image.width && y >= 0 && y < game->image.height)
			my_store_pixel_in_image(&game->image, (int)x, (int)y, COLOR_YELLOW);
		x += x_inc;
		y += y_inc;
	}

	/* if debug is enabled, mark the hit pixel with side-specific color */
	if (game->ray.debug_rays && hit_side != -1)
	{
		int hx = ray_pixel_x;
		int hy = ray_pixel_y;
		int color = (hit_side == 0) ? COLOR_RED : COLOR_BLUE; /* vertical=red, horizontal=blue */
		if (hx >= 0 && hx < game->image.width && hy >= 0 && hy < game->image.height)
			my_store_pixel_in_image(&game->image, hx, hy, color);
	}
}


