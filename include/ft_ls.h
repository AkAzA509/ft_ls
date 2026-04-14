#pragma once

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../src/libft/include/libft.h"

#include <stdio.h>

#define GREEN "\033[92m"
#define WHITE "\033[97m"
#define BLUE "\033[94m"
#define RED "\033[91m"
#define PURPLE "\033[38;2;255;105;255m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

#define BLD_WHITE BOLD WHITE
#define BLD_RED BOLD RED
#define BLD_BLUE BOLD BLUE
#define BLD_GREEN BOLD GREEN
#define BLD_PURPLE BOLD PURPLE

typedef struct s_entry {
	char			*name;
	struct stat		entry_info;
}					t_entry;

typedef struct s_param {
	char			**path;
	bool			l_opt;
	bool			R_opt;
	bool			a_opt;
	bool			r_opt;
	bool			t_opt;
	unsigned char	exit_code;
}					t_param;

// print helper
void	print_help();
void	print_error(char* msg);
void	print_error_args(char arg);

// parsing
void	parse_parameter(char *av[], t_param *params);
size_t	tab_len(char **tab);
int		name_cmp(const char *a, const char *b) ;

// cleaning
void	exiting(int code, t_param *params);

// listing
void	listing(t_param *params);