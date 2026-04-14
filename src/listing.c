#include "../include/ft_ls.h"
#include <string.h>

static t_entry	*load_entries(DIR *dir, char *dir_path, t_param *params, size_t *count) {
	struct dirent	*entry;
	size_t			capacity = 10;
	t_entry			*entries = malloc(sizeof(t_entry) * capacity);

	*count = 0;
	if (!entries)
		return NULL;

	while ((entry = readdir(dir)) != NULL)
	{
		if (!params->a_opt && entry->d_name[0] == '.')
			continue;

		if (*count >= capacity)
		{
			capacity *= 2;
			t_entry *new_entries = malloc(sizeof(t_entry) * capacity);
			if (!new_entries) {
				free(entries);
				return NULL;
			}
			memcpy(new_entries, entries, sizeof(t_entry) * (*count));
			free(entries);
			entries = new_entries;
		}

		char *tmp_path = ft_strjoin(dir_path, "/");
		if (!tmp_path) {
			free(entries);
			return NULL;
		}
		char *full_path = ft_strjoin(tmp_path, entry->d_name);
		free(tmp_path);
		if (!full_path) {
			free(entries);
			return NULL;
		}

		entries[*count].name = ft_strdup(entry->d_name);
		if (!entries[*count].name) {
			free(full_path);
			free(entries);
			return NULL;
		}
		
		if (stat(full_path, &entries[*count].entry_info) != 0) {
			print_error("stat failed\n");
			free(full_path);
			free(entries[*count].name);
			continue;
		}
		free(full_path);
		(*count)++;
	}
	return entries;
}

static int	name_cmp(const char *a, const char *b) {
	size_t	na = ft_strlen(a);
	size_t	nb = ft_strlen(b);

	if (na > nb)
		return (ft_strncmp(a, b, na + 1));
	return (ft_strncmp(a, b, nb + 1));
}

static bool	should_shift_time(t_entry left, t_entry right) {
	if (left.entry_info.st_mtime != right.entry_info.st_mtime)
		return (left.entry_info.st_mtime < right.entry_info.st_mtime);
	return (name_cmp(left.name, right.name) > 0);
}

static void	sort_by_time(t_entry *entries, size_t count) {
	for (size_t i = 1; i < count; i++) {
		t_entry key = entries[i];
		int j = i - 1;
		
		while (j >= 0 && should_shift_time(entries[j], key)) {
			entries[j + 1] = entries[j];
			j--;
		}
		entries[j + 1] = key;
	}
}

static void sort_entries(t_entry *entries, size_t count) {
	for (size_t i = 1; i < count; i++) {
		t_entry key = entries[i];
		int j = i - 1;
		
		while (j >= 0 && name_cmp(entries[j].name, key.name) > 0) {
			entries[j + 1] = entries[j];
			j--;
		}
		entries[j + 1] = key;
	}
}

static void display_size(size_t bytes) {
	size_t unit, whole, frac, rem;

	if (bytes >= 1024UL * 1024UL) {
		unit = 1024UL * 1024UL;
		whole = bytes / unit;
		rem = bytes % unit;
		frac = (rem * 10 + unit / 2) / unit;
		if (frac == 10) {
			whole += 1;
			frac = 0;
		}
		ft_printf("%zu.%zu MB", whole, frac);
	}
	else if (bytes >= 1024UL) {
		unit = 1024UL;
		whole = bytes / unit;
		rem = bytes % unit;
		frac = (rem * 10 + unit / 2) / unit;
		if (frac == 10) {
			whole += 1;
			frac = 0;
		}
		ft_printf("%zu.%zu KB", whole, frac);
	}
	else {
		ft_printf("%zu B", bytes);
	}
}

static void	display_long_entry(int start, int end, int step, t_entry *entries) {
	for (int i = start; i != end; i += step) {
		// char *group, *user = NULL;
		display_size(entries[i].entry_info.st_size);
		ft_printf(" %s\n", entries[i].name);
	}
}

static void display_entries(t_entry *entries, size_t count, bool multi_dir, t_param *param) {
	int start, end, step;

	if (param->r_opt) {
		start = (int)count - 1;
		end = -1;
		step = -1;
	}
	else {
		start = 0;
		end = (int)count;
		step = 1;
	}

	if (param->l_opt)
		display_long_entry(start, end, step, entries);
	else {
		for (int i = start; i != end; i += step) {
			if (S_ISDIR(entries[i].entry_info.st_mode))
				ft_printf(BLD_BLUE"%s  "RESET, entries[i].name);
			else
				ft_printf(BLD_WHITE"%s  "RESET, entries[i].name);
		}
	}
	ft_printf("%s", multi_dir ? "\n\n" : "\n");
}

static void free_entries(t_entry *entries, size_t count)
{
	for (size_t i = 0; i < count; i++)
		free(entries[i].name);
	free(entries);
}

void listing(t_param *params)
{
	char	**path_tab = params->path;
	int		path_count;
	int		start;
	int		end;
	int		step;

	bool multi_dir = tab_len(path_tab) > 1 ? true : false;
	path_count = (int)tab_len(path_tab);
	if (params->r_opt) {
		start = path_count - 1;
		end = -1;
		step = -1;
	}
	else {
		start = 0;
		end = path_count;
		step = 1;
	}

	for (int i = start; i != end; i += step) {
		DIR *dir = opendir(path_tab[i]);
		if (!dir) {
			print_error("opendir failed\n");
			continue;
		}

		size_t count = 0;
		t_entry *entries = load_entries(dir, path_tab[i], params, &count);
		closedir(dir);

		if (!entries) {
			print_error("malloc failed\n");
			continue;
		}

		if (params->t_opt)
			sort_by_time(entries, count);
		else
			sort_entries(entries, count);

		if(multi_dir)
			ft_printf("%s:\n", path_tab[i]);

		display_entries(entries, count, multi_dir, params);

		free_entries(entries, count);
	}
}