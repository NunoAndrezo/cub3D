#include "../inc/cub3d.h"

static bool	is_colision(t_game *game, float nx, float ny);
static bool	check_diagonally_strafing(t_game *game);

/* Compute rotation delta in DEGREES. The old code used a radian delta
	of (PLAYER_MOV_SPEED / 50.0f). To preserve the previous angular
	speed after switching to degrees, convert that radian delta to
	degrees using `rad_to_deg`.
*/
void change_player_rot(t_game *game)
{ // how can I make rotation speed independent of frame rate? and more fluid? answer: use delta time between frames to calculate rotation delta. We do that by swaping to degrees and using a fixed degrees per second speed
	/*
	Convert previous per-update rotation delta to a per-second value, then
	scale with the elapsed time for a smooth, frame-rate independent rotation.
	The prior code used a small radian delta (0.07 rad) per update at ~16ms
	which is equivalent to roughly (0.07 rad * 62.5) per second. We preserve
	that behavior by computing degrees/sec and multiplying by delta time.
	*/
	float dt_seconds = (float)game->delta_time / 1000.0f;
	float rot_deg_per_update = rad_to_deg(0.07f);
	const float updates_per_sec = 1000.0f / 16.0f; /* 62.5, matches previous fixed-step */
	float rot_deg_per_sec = rot_deg_per_update * updates_per_sec;
	float rot_delta_deg = rot_deg_per_sec * dt_seconds;
	/* apply runtime rotation multiplier */
	rot_delta_deg *= game->player.player_rot_multiplier;

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

void change_player_mov(t_game *game)
{
	float	nx;
	float	ny;
	bool	strafing_diagonally;
	nx = game->player.pos_x;
	ny = game->player.pos_y;
	strafing_diagonally = check_diagonally_strafing(game);

	/* Compute a per-second movement in tile units that preserves prior
	   behaviour. The previous code advanced by (PLAYER_MOV_SPEED / ONE_TILE_SIDE)
	   per fixed update (16 ms). So we convert that to tiles/sec and scale by
	   delta-time (seconds). */
	float base_per_update = (float)PLAYER_MOV_SPEED / (float)ONE_TILE_SIDE; /* tiles per 16ms-update */
	const float updates_per_sec = 1000.0f / 16.0f; /* 62.5 */
	float tiles_per_sec = base_per_update * updates_per_sec;
	float dt = (float)game->delta_time / 1000.0f; /* seconds */
	float displacement = tiles_per_sec * dt; /* tiles to move this frame */
	/* apply runtime linear speed multiplier */
	displacement *= game->player.player_speed_multiplier;

	if (strafing_diagonally)
		displacement /= 1.4f; /* reduce diagonal speed as before */

	/* Move in fractional tile units scaled by delta-time */
	if (game->player.player_mov_left)
	{
		ny += game->player.player_delta_x * displacement;
		nx -= game->player.player_delta_y * displacement;
	}
	else if (game->player.player_mov_right)
	{
		ny -= game->player.player_delta_x * displacement;
		nx += game->player.player_delta_y * displacement;
	}
	if (game->player.player_mov_forward)
	{
		nx -= game->player.player_delta_x * displacement;
		ny -= game->player.player_delta_y * displacement;
	}
	else if (game->player.player_mov_backward)
	{
		nx += game->player.player_delta_x * displacement;
		ny += game->player.player_delta_y * displacement;
	}
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