#include "../include/ft_ls.h"

int main(int ac, char*av[]) {
	if (ac <= 1)
		return 1;
	else
		parse_parameter(++av);

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
	return 0;
}