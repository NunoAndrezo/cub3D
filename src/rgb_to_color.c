/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:08:06 by nuno              #+#    #+#             */
/*   Updated: 2026/01/05 01:20:10 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Converts an RGB array to a single integer color value
// rgb[0] << 16: Shifts the Red value to the high 8 bits (0xRR0000).
// rgb[1] << 8: Shifts the Green value to the middle 8 bits (0x00GG00).
// rgb[2]: Keeps the Blue value in the lowest 8 bits (0x0000BB).
// |: Combines them into a single integer 0xRRGGBB

int	rgb_to_color(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | (rgb[2]));
}
