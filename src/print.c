#include "../include/ft_ls.h"

void	print_help() {
	ft_printf("Usage: ft_ls [OPTIONS] [FILE]...\n\n");
	ft_printf("Arguments:\n\t[FILE]...  [default: .]\n\n");
	ft_printf("Options:\n");
	ft_printf("\t-a, \tDo not ignore entries starting with .\n");
	ft_printf("\t-l, \tDisplay extended file metadata as a table\n");
	ft_printf("\t-h, \tPrint help information\n");
	ft_printf("\t-R, \tRecurse into directories\n");
	ft_printf("\t-t, \tSort by time modified\n");
	ft_printf("\t-r, \tReverse the order of the sort\n");
}

void	print_error(char* msg) {
	ft_printf(BLD_RED"Error: "RESET);
	ft_printf("%s", msg);
}

void	print_error_args(char arg) {
	ft_printf(BLD_RED"Error: "RESET);
	ft_printf("unexpected argument '-%c' found\n\n", arg);
	ft_printf("Usage: ft_ls [OPTIONS] [FILE]...\n\n");
	ft_printf("For more information, try '-h'.\n");
}