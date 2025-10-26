#include "../inc/cub3d.h"

static void	ft_bzero(void *s, size_t n);

int main(int ac, char **av)
{
	t_game	game;

	parse(ac, av);
	ft_bzero(&game, sizeof(t_game));
	handle_map(av[1], &game);
	
	return (0);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}