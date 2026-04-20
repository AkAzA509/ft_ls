#include "../include/ft_ls.h"

void	free_split(char **tab)
{
	if (!tab)
		return;
	for (size_t i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

void	exiting(int code, t_param *params) {
	if (params->path)
		free_split(params->path);
	exit(code);
}

int main(int ac, char*av[]) {
	if (ac < 1)
		return 1;
	
	t_param params = {
		.a_opt = false,
		.R_opt = false,
		.r_opt = false,
		.l_opt = false,
		.t_opt = false,
		.path = NULL,
		.exit_code = 0
	};
	
	parse_parameter(++av, &params);

	listing(&params);

	exiting(params.exit_code, &params);
}