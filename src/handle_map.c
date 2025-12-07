#include "../inc/cub3d.h"

static int count_and_store_number_of_lines(t_game *game, char *map_file);
static void copy_map(char *map_file, t_game *game);
static void allocate_map(t_game *game);
static bool is_texture_or_color_line(t_game *game, char *line);
static void save_parameteres(t_game *game, char *line);
static void save_color(t_game *game, char *line, char type);
static void parse_rgb_values(char *line, int *r, int *g, int *b);

void handle_map(char *map_file, t_game *game)
{
	ft_bzero(&game->map, sizeof(t_map));
	ft_bzero(&game->textures, sizeof(t_texture));
	game->map.map_file = map_file;
	if (!game->map.map_file)
		perror("Error: Memory allocation for game->map.map_file failed\n"), exit(EXIT_FAILURE);
	if (count_and_store_number_of_lines(game, game->map.map_file) <= 0)
		perror("Error: Map file is empty\n"), exit(EXIT_FAILURE);
	if (!game->textures.north_texture || !game->textures.south_texture ||
		!game->textures.west_texture || !game->textures.east_texture)
		perror("Error: Missing texture paths in map file\n"), exit(EXIT_FAILURE);
	copy_map(game->map.map_file, game);
}

static int count_and_store_number_of_lines(t_game *game, char *map_file)
{
	char	*line;
	int		i;
	int		fd;
	bool	in_map;
	int		first_time;

	first_time = -1;
	i = 0;
	in_map = false;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		perror("Error: Cannot open map file\n"), exit(EXIT_FAILURE);
	game->map.y_max = 0;
	line = get_next_line(fd);
	while (line)
	{
		printf("Read line: %s", line);
		fflush(stdout);
		++i;
		if (is_texture_or_color_line(game, line) == false)
		{
			if (first_time == -1)
			{
				first_time = 1;
				game->map.y_start = i;
			}
			in_map = true;
		}
		if (in_map == true)
			game->map.y_max++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	printf("Map has %d lines\n", game->map.y_max);
	return (game->map.y_max);
}

static bool is_texture_or_color_line(t_game *game, char *line)
{
	printf("Checking if line is texture or color line: %s\n", line);
	if (!line)
	{
		perror("Error: Parsing textures and colors.\n");
		exit(1);
	}
	if (!line[0] || line[0] == '\n' || line[0] == ' ')
		return (true);
	else if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
		ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		save_parameteres(game, line);
		return (true);
	}
	return (false);
}

static void save_parameteres(t_game *game, char *line)
{
	printf("Saving parameter line: %s\n", line);
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->textures.north_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->textures.south_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->textures.west_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->textures.east_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		save_color(game, line + 2, 'F');
	else if (ft_strncmp(line, "C ", 2) == 0)
		save_color(game, line + 2, 'C');
	else
	{
		perror("Error: Invalid texture or color line in map file\n");
		exit(EXIT_FAILURE);
	}
}

static void save_color(t_game *game, char *line, char type)
{
	int	r;
	int	g;
	int	b;

	parse_rgb_values(line, &r, &g, &b);
	if (type == 'F')
	{
		game->textures.floor_color[0] = r;
		game->textures.floor_color[1] = g;
		game->textures.floor_color[2] = b;
	}
	else if (type == 'C')
	{
		game->textures.ceiling_color[0] = r;
		game->textures.ceiling_color[1] = g;
		game->textures.ceiling_color[2] = b;
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		perror("Error: RGB color values must be between 0 and 255\n");
		exit(EXIT_FAILURE);
	}
}

static void parse_rgb_values(char *line, int *r, int *g, int *b)
{
    // Accepts a string like "220,100,0" (possibly with spaces)
    // and parses the three integer values.
    char *ptr = line;
    while (*ptr == ' ' || *ptr == '\t') ptr++; // skip leading whitespace
    *r = ft_atoi(ptr);
    while (*ptr && *ptr != ',') ptr++;
    if (*ptr == ',') ptr++;
    *g = ft_atoi(ptr);
    while (*ptr && *ptr != ',') ptr++;
    if (*ptr == ',') ptr++;
    *b = ft_atoi(ptr);
}

static void copy_map(char *map_file, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	allocate_map(game);
	// need to see what I have to do white empty spaces or lines ? replace with 0 probably or 1 or i cut or ignore them
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		perror("Error: Cannot open map file\n"), exit(EXIT_FAILURE);
	line = get_next_line(fd);
	if (!line)
		perror("Error: Empty or invalid map file\n"), close(fd), exit(EXIT_FAILURE);
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	i++;
//	game->map.map[i++] = ft_strdup(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!line)
			break ;
		if (game->map.y_start <= i)
			game->map.map[i++] = ft_strdup(line);
		i++;
	}
	close(fd);
}

static void allocate_map(t_game *game)
{
	game->map.map = (char **)ft_calloc((game->map.y_max + 1), sizeof(char *));
	if (!game->map.map)
	{
		perror("Error: Memory allocation failed\n");
		//maybe free other stuff here
		exit(EXIT_FAILURE);
	}
	game->map.map[game->map.y_max] = NULL;
}
