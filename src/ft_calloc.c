/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:04:28 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 14:24:51 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	*ft_calloc_helper(size_t c);

void	*ft_calloc(size_t count, size_t size)
{
	size_t	ct;

	ct = count * size;
	if (count > size && size != 0 && size != 1)
	{
		if (count > ct)
			return (NULL);
	}
	else if (count < size && count != 0 && count != 1)
	{
		if (size > ct)
			return (NULL);
	}
	else if (count == size && size != 0)
	{
		if (ct < count)
			return (NULL);
	}
	return (ft_calloc_helper(ct));
}

static void	*ft_calloc_helper(size_t c)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(c);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < c)
		ptr[i++] = 0;
	return (ptr);
}
