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

//MAP RULES TO BE IMPLEMENTED IN PARSING AND MAP VALIDATION: wtf is this?
//• The map must be composed only by the characters '0', '1', 'N', 'S', 'E', 'W' and
//' ' (space character).
//◦ '0' : empty space where the player can walk.
//◦ '1' : wall.
//◦ 'N', 'S', 'E', 'W' : player's starting position and orientation (North, South,
//East and West respectively). There must be exactly one occurrence of one of
//these characters in the map.
//◦ ' ' (space): nothingness, i.e., not part of the map.
//• The map must be rectangular: each line must have the same length. You can
//consider the lines shorter than the longest one as being completed with spaces
//on the right.

//The map must be closed/surrounded by walls, if not the program must return
//an error.
//◦ Except for the map content, each type of element can be separated by one or
//more empty lines.
//◦ Except for the map content which always has to be the last, each type of
//element can be set in any order in the file.
//◦ Except for the map, each type of information from an element can be separated
//by one or more spaces.
//◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
//map and are up to you to handle. You must be able to parse any kind of map,
//as long as it respects the rules of the map.