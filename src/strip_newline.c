/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_newline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:08:20 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 13:08:21 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Removes trailing newline and carriage return from a string, in-place
void strip_newline(char *str)
{
	int	len;

	if (!str)
		return;
	len = strlen(str);
	while (len > 0 && (str[len-1] == '\n' || str[len-1] == '\r'))
	{
		str[len-1] = '\0';
		len--;
	}
}
