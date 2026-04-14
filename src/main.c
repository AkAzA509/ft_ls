#include "../include/ft_ls.h"

static void	free_split(char **tab)
{
	if (!tab)
		return;
	while (*tab) {
		free(*tab);
		tab++;
	}
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

	// stat(2);

	// DIR	*dir = opendir(".");
	// if (!dir)
	// 	return printf("error\n");

	// struct dirent	*entry;
	// while ((entry = readdir(dir)) != NULL) {
	// 	// printf("%d\t%s\n", entry->d_type, entry->d_name);
	// 	printf("%s  ", entry->d_name);
	// }

	// closedir(dir);
	return params.exit_code;
}