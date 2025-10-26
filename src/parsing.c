#include "../inc/cub3d.h"

static void	check_map_name(char *map);

void	parse(int ac, char **av)
{
	if (ac != 2)
		fprintf(stderr, "Error: Wrong number of arguments.\n"), exit(1);
	check_map_name(av[1]);
}

static void	check_map_name(char *map)
{
	int	len;

	if (!map || !map[0])
		fprintf(stderr, "Error: Wrong argument av[1].\n"), exit(1);
	len = strlen(map); // swap for ft_strlen
	len--;
	if (!(map[len -3] == '.' && map[len -2] == 'c' && map[len -1] == 'u' && map[len] == 'b'))
		fprintf(stderr, "Error: Invalid map extension <*.cub>\n"), exit(1);
}