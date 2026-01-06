/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_me_baby2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:17:45 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 23:37:54 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_split_values(char **values)
{
	int	i;

	i = 0;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
}
