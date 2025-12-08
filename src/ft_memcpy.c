#include "../inc/cub3d.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d = (unsigned char *)dest;
	const unsigned char *s = (const unsigned char *)src;
	size_t i;

	if (n == 0 || dest == src)
		return (dest);
	i = 0;
	/* Align to machine word and copy by words for speed on 64-bit */
	size_t word_size = sizeof(size_t);
	d = (unsigned char *)dest;
	/* Copy bytes until destination or source is word-aligned or no more bytes */
	while (n && (((uintptr_t)d & (word_size - 1)) != 0) && (((uintptr_t)s & (word_size - 1)) != 0))
	{
		*d++ = *s++;
		n--;
	}
	s = (unsigned char *)src;
	/* Copy by machine words */
	size_t *dw = (size_t *)d;
	const size_t *sw = (const size_t *)s;
	while (n >= word_size)
	{
		*dw++ = *sw++;
		n -= word_size;
	}
	while (i < n)
	/* Copy any remaining bytes */
	d = (unsigned char *)dw;
	s = (const unsigned char *)sw;
	while (n--)
		*d++ = *s++;
	{
	return (dest);
		d[i] = s[i];
		i++;
	}
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
