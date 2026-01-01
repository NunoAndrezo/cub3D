#include "../inc/cub3d.h"

static int count_and_store_number_of_lines_and_check_textures_colors(t_game *game, char *map_file);
static void copy_map(char *map_file, t_game *game);
static void allocate_map(t_game *game);
static bool is_texture_or_color_line(t_game *game, char *line, int fd);
static void save_parameteres(t_game *game, char *line, int fd);
static bool save_color(t_game *game, char *line, char type);
static bool parse_rgb_values(char *line, int *r, int *g, int *b);
static void free_split_values(char **values);

void handle_map(char *map_file, t_game *game)
{
	ft_bzero(&game->map, sizeof(t_map));
	ft_bzero(&game->textures, sizeof(t_texture));
	game->map.map_file = map_file;
	if (!game->map.map_file)
		perror("Error\nNo map file provided\n"), exit(EXIT_FAILURE);
	if (count_and_store_number_of_lines_and_check_textures_colors(game, game->map.map_file) <= 0)
		perror("Error\nMap file is empty\n"), exit(EXIT_FAILURE);
	if (!game->textures.north_texture || !game->textures.south_texture ||
		!game->textures.west_texture || !game->textures.east_texture)
		perror("Error\nMissing texture paths in map file\n"), free_game(game), exit(EXIT_FAILURE);
	if (game->texture_n == false || game->texture_s == false ||
		game->texture_w == false || game->texture_e == false ||
		game->color_f == false || game->color_c == false)
		perror("Error\nNot all required textures and colors were specified\n"), free_game(game), exit(EXIT_FAILURE);
	copy_map(game->map.map_file, game);
}

static int count_and_store_number_of_lines_and_check_textures_colors(t_game *game, char *map_file)
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
		perror("Error\nCannot open map file\n"), exit(EXIT_FAILURE);
	game->map.y_max = 0;
	line = get_next_line(fd);
	while (line)
	{
		++i;
		if (is_texture_or_color_line(game, line, fd) == false)
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
	return (game->map.y_max);
}

static bool is_texture_or_color_line(t_game *game, char *line, int fd)
{
	if (!line)
	{
		perror("Error\nParsing textures and colors.\n");
		exit(1);
	}
	if (line[0] == '\0' || line[0] == '\n' || line[0] == ' ' || line[0] == '\t')
		return (true);
	else if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 ||
		ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0 ||
		ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		save_parameteres(game, line, fd);
		return (true);
	}
	return (false);
}

static void save_parameteres(t_game *game, char *line, int fd)
{
	bool		success;
	int			i;

	success = true;
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		i = 2;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i])
		{
			game->textures.north_texture = ft_strdup(line + i);
			strip_newline(game->textures.north_texture);
			game->texture_n = true;
		}
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		i = 2;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i])
		{
			game->textures.south_texture = ft_strdup(line + i);
			strip_newline(game->textures.south_texture);
			game->texture_s = true;
		}
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		i = 2;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i])
		{
			game->textures.west_texture = ft_strdup(line + i);
			strip_newline(game->textures.west_texture);
			game->texture_w = true;
		}
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		i = 2;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i])
		{
			game->textures.east_texture = ft_strdup(line + i);
			strip_newline(game->textures.east_texture);
			game->texture_e = true;
		}
	}
	else if (ft_strncmp(line, "F", 1) == 0)
	{
		i = 1;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i] && line[i] >= '0' && line[i] <= '9')
		{
			success = save_color(game, line + i, 'F');
			game->color_f = true;
		}
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		i = 1;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i] && line[i] >= '0' && line[i] <= '9')
		{
			success = save_color(game, line + i, 'C');
			game->color_c = true;
		}
	}
	else
	{
		perror("Error\nInvalid texture or color line in map file\n");
		close(fd);
		free(line);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	if (success == false)
	{
		close(fd);
		free(line);
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

static bool save_color(t_game *game, char *line, char type)
{
	int	r;
	int	g;
	int	b;

	r = -1;
	g = -1;
	b = -1;
	if (!parse_rgb_values(line, &r, &g, &b))
		return false;
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
		return (perror("Error\nRGB color values must be between 0 and 255\n"), false);
	return (true);
}

static bool parse_rgb_values(char *line, int *r, int *g, int *b)
{
	char	**values;
	int		i;

	values = NULL;
	values = ft_split(line, ',');
	if (!values)
	{
		free_split_values(values);
		perror("Error\nMemory allocation failed while parsing RGB values\n");
		return (false);
	}
	i = 0;
	while (values[i])
		i++;
	if (i != 3)
	{
		free_split_values(values);
		perror("Error\nRGB color line must contain exactly 3 values\n");
		return (false);
	}
	*r = ft_atoi(values[0]);
	*g = ft_atoi(values[1]);
	*b = ft_atoi(values[2]);
	free_split_values(values);
	return (true);
}

static void free_split_values(char **values)
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

static void copy_map(char *map_file, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 1;
	allocate_map(game);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		perror("Error\nCannot open map file\n"), exit(EXIT_FAILURE);
	line = get_next_line(fd);
	if (!line)
		perror("Error\nEmpty or invalid map file\n"), close(fd), exit(EXIT_FAILURE);
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!line)
			break ;
		if (game->map.y_start <= i)
			game->map.map[i - game->map.y_start] = ft_strdup(line);
	}
	close(fd);
}

static void allocate_map(t_game *game)
{
	game->map.map = (char **)ft_calloc((game->map.y_max + 1), sizeof(char *));
	if (!game->map.map)
	{
		perror("Error\nMemory allocation failed\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	game->map.map[game->map.y_max] = NULL;
}
