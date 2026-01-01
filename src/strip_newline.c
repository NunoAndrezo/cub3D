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
