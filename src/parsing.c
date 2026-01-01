#include "../inc/cub3d.h"

static void	check_map_name(char *map);

void	parse(int ac, char **av)
{
	if (ac != 2)
		perror("Error\nWrong number of arguments.\n"), exit(1);
	check_map_name(av[1]);
}

static void	check_map_name(char *map)
{
	int	len;

	if (!map || !map[0])
		perror("Error\nWrong argument av[1].\n"), exit(1);
	len = ft_strlen(map);
	len--;
	if (!(map[len -3] == '.' && map[len -2] == 'c' && map[len -1] == 'u' && map[len] == 'b'))
		perror("Error\nInvalid map extension <*.cub>\n"), exit(1);
}
