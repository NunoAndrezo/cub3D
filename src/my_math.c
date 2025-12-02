#include "../inc/cub3d.h"

static float	rad_to_deg(float angle_in_radians)
{
	return (angle_in_radians * 180.0f / PI_VALUE);
}

static float deg_to_rad(float angle_in_degrees)
{
	return (angle_in_degrees * (PI_VALUE / 180.0f));
}
