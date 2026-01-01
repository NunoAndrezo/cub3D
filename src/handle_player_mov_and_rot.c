#include "../inc/cub3d.h"

static bool	is_colision(t_game *game, float nx, float ny);
static bool	check_diagonally_strafing(t_game *game);

/* Compute rotation delta in DEGREES. The old code used a radian delta
	of (PLAYER_MOV_SPEED / 50.0f). To preserve the previous angular
	speed after switching to degrees, convert that radian delta to
	degrees using `rad_to_deg`.
*/
void change_player_rot(t_game *game)
{
	float rot_delta_deg = rad_to_deg((float)PLAYER_MOV_SPEED / 50.0f); // degrees per update. rotation delta degrees means how many degrees to rotate per update
	// we divide by 50 because 50 updates per second is 20ms per update, so we get a smooth rotation speed
	if (game->player.player_rot_left)
	{
		game->player.player_angle -= rot_delta_deg;
		if (game->player.player_angle < 0.0f)
			game->player.player_angle += 360.0f;
		game->player.player_delta_x = -cosf(deg_to_rad(game->player.player_angle)); // -cos because 0 degrees is to the right and the map is "upside down" in terms of y axis
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