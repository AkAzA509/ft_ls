#include "../include/ft_ls.h"

int main(int ac, char*av[]) {
	if (ac <= 1)
		return 1;
	else
		parse_parameter(ac, av);
}