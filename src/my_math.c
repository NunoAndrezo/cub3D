/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:43 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 23:37:42 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	rad_to_deg(float angle_in_radians)
{
	return (angle_in_radians * 180.0f / PI_VALUE);
}

float	deg_to_rad(float angle_in_degrees)
{
	return (angle_in_degrees * (PI_VALUE / 180.0f));
}
