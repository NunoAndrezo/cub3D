/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 14:29:11 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 14:50:40 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_memcpy_word(
	unsigned char **d,
	const unsigned char **s,
	size_t *n)
{
	size_t			*dw;
	const size_t	*sw;

	dw = (size_t *)(*d);
	sw = (const size_t *)(*s);
	while (*n >= sizeof(size_t))
	{
		*dw++ = *sw++;
		*n -= sizeof(size_t);
	}
	*d = (unsigned char *)dw;
	*s = (const unsigned char *)sw;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				word_size;

	if (n == 0 || dest == src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	word_size = sizeof(size_t);
	while (n > 0
		&& ((uintptr_t)d % word_size != 0
			|| (uintptr_t)s % word_size != 0))
	{
		*d++ = *s++;
		n--;
	}
	ft_memcpy_word(&d, &s, &n);
	while (n--)
		*d++ = *s++;
	return (dest);
}

void	*ft_memcpy_normal(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
