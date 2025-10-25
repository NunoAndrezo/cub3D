#include "../inc/parsing.h"

int main(int ac, char **av)
{
	parse(ac, av);
	handle_map(av[1]);
	
	return (0);
}