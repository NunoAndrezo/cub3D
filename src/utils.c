#include "../inc/cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		j;
	char	*ptr;

	j = 0;
	ptr = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	while (s[j])
	{
		ptr[j] = s[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
