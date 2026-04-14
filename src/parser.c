#include "../include/ft_ls.h"

static size_t	path_count(char **tab) {
	size_t i = 0;

	if (!tab)
		return 0;
	while (tab[i])
		i++;
	return i;
}

static bool	push_back_path(t_param *params, const char *path) {
	char	**new_tab;
	size_t i = 0;
	size_t count;

	count = path_count(params->path);
	new_tab = malloc(sizeof(char *) * (count + 2));
	if (!new_tab)
		return false;
	while (i < count) {
		new_tab[i] = params->path[i];
		i++;
	}
	new_tab[count] = ft_strdup(path);
	if (!new_tab[count]) {
		free(new_tab);
		return false;
	}
	new_tab[count + 1] = NULL;
	free(params->path);
	params->path = new_tab;
	return true;
}

static void	parse_options(char *option, t_param *params) {
	bool is_help = false;

	while (*option) {
		if (*option == 'a')
			params->a_opt = true;
		else if (*option == 'R')
			params->R_opt = true;
		else if (*option == 'l')
			params->l_opt = true;
		else if (*option == 'r')
			params->r_opt = true;
		else if (*option == 't')
			params->t_opt = true;
		else if (*option == 'h')
			is_help = true;
		else {
			print_error_args(*option);
			exiting(2, params);
		}
		++option;
	}

	if (is_help) {
		print_help();
		exiting(0, params);
	}
}

static void	parse_path(char *path, t_param *params) {
	struct stat stats;
	if (stat(path, &stats)) {
		perror("stat error: "); // a changer pour un bon message d'erreur
		params->exit_code = 2;
		return ;
	}
	if (!push_back_path(params, path)) {
		print_error("malloc failed\n");
		exiting(1, params);
	}
}

void	parse_parameter(char *av[], t_param *params) {
	while (*av) {
		if (*av && **av == '-')
			parse_options(*av + 1, params);
		else if (*av && **av != '-')
			parse_path(*av, params);
		av++;
	}

	if (!params->path && params->exit_code == 0) {
		if (!push_back_path(params, "."))
			print_error("malloc failed\n");
	}
	else if (!params->path && params->exit_code > 0)
		exiting(params->exit_code, params);

	ft_printf("Params check: a:%s, R:%s, l:%s, r:%s, t:%s\n",
		params->a_opt ? "true" : "false",
		params->R_opt ? "true" : "false",
		params->l_opt ? "true" : "false",
		params->r_opt ? "true" : "false",
		params->t_opt ? "true" : "false"
	);

	if (params->path) {
		for (size_t i = 0; params->path[i]; i++)
			ft_printf("%s\n", params->path[i]);
	}
}