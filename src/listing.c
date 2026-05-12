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

		if (*count >= capacity) {
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
		
		if (lstat(full_path, &entries[*count].entry_info) != 0) {
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

static int	compare_mtime(struct stat left, struct stat right) {
	if (left.st_mtim.tv_sec < right.st_mtim.tv_sec)
		return (-1);
	if (left.st_mtim.tv_sec > right.st_mtim.tv_sec)
		return (1);
	if (left.st_mtim.tv_nsec < right.st_mtim.tv_nsec)
		return (-1);
	if (left.st_mtim.tv_nsec > right.st_mtim.tv_nsec)
		return (1);
	return (0);
}

static bool	should_shift_time(t_entry left, t_entry right) {
	int cmp = compare_mtime(left.entry_info, right.entry_info);

	if (cmp != 0)
		return (cmp < 0);
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

static void	sort_entries(t_entry *entries, size_t count) {
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

static size_t	size_digits(size_t n) {
	size_t d;

	d = 1;
	while (n >= 10) {
		n /= 10;
		d++;
	}
	return d;
}

static size_t	max_size_width(t_entry *entries, size_t count) {
	size_t max_width = 1;
	size_t current;

	for (size_t i = 0; i < count; i++) {
		current = size_digits((size_t)entries[i].entry_info.st_size);
		if (current > max_width)
			max_width = current;
	}
	return max_width;
}

static size_t max_link_width(t_entry *entries, size_t count) {
	size_t max_width = 1;
	size_t current;

	for (size_t i = 0; i < count; i++) {
		current = size_digits((size_t)entries[i].entry_info.st_nlink);
		if (current > max_width)
			max_width = current;
	}
	return max_width;
}

static void	display_size(size_t bytes, size_t width) {
	size_t current = size_digits(bytes);

	while (current < width) {
		ft_printf(" ");
		current++;
	}
	ft_printf("%zu ", bytes);
}

static void	display_user(uid_t nb) {
	struct passwd	*pw = getpwuid(nb);
	char *user = (pw && pw->pw_name) ? pw->pw_name : "?";
	ft_printf("%s ", user );
}

static void	display_group(gid_t nb) {
	struct group	*gr = getgrgid(nb);
	char *group = (gr && gr->gr_name) ? gr->gr_name : "?";
	ft_printf("%s ", group);
}

static bool	display_right(struct stat stats, size_t width) {
	char right[11];

	right[0] = S_ISDIR(stats.st_mode) ? 'd' : S_ISLNK(stats.st_mode) ? 'l' : '-';
	right[1] = (stats.st_mode & S_IRUSR) ? 'r' : '-';
	right[2] = (stats.st_mode & S_IWUSR) ? 'w' : '-';
	right[3] = (stats.st_mode & S_IXUSR) ? 'x' : '-';
	right[4] = (stats.st_mode & S_IRGRP) ? 'r' : '-';
	right[5] = (stats.st_mode & S_IWGRP) ? 'w' : '-';
	right[6] = (stats.st_mode & S_IXGRP) ? 'x' : '-';
	right[7] = (stats.st_mode & S_IROTH) ? 'r' : '-';
	right[8] = (stats.st_mode & S_IWOTH) ? 'w' : '-';
	right[9] = (stats.st_mode & S_IXOTH) ? 'x' : '-';
	right[10] = '\0';

	ft_printf("%s ", right);
	size_t digits = size_digits((size_t)stats.st_nlink);
	while (digits < width) {
		ft_printf(" ");
		digits++;
	}
	ft_printf("%zu ", (size_t)stats.st_nlink);
	if (right[0] == 'l')
		return true;
	return false;
}

static void	display_date(struct stat stats) {
	time_t	timer = stats.st_mtime;
	
	char	*time = ctime(&timer);
	if (time) {
		time = ft_substr(time, 4, 12);
		ft_printf("%s", time);
		free(time);
	}
}

static void	display_total(int start, int end, int step, t_entry *entries) {
	size_t	total = 0;
	
	for (int i = start; i != end; i += step)
		total += ((size_t)entries[i].entry_info.st_blocks + 1) / 2;

	ft_printf("total %zu\n", total);
}

static char	**display_long_entry(int start, int end, int step, t_entry *entries, size_t size_width, size_t link_width, int flag) {
	if (!flag)
		display_total(start, end, step, entries);

	char	**dir = NULL;
	for (int i = start; i != end; i += step) {
		bool is_link = display_right(entries[i].entry_info, link_width);

		display_user(entries[i].entry_info.st_uid);
		display_group(entries[i].entry_info.st_gid);
		display_size((size_t)entries[i].entry_info.st_size, size_width);
		display_date(entries[i].entry_info);

		if (S_ISDIR(entries[i].entry_info.st_mode)) {
			ft_printf(BLD_BLUE" %s"RESET, entries[i].name);
				dir = push_back_path(dir, entries[i].name);
		}
		else
			ft_printf(BLD_WHITE" %s"RESET, entries[i].name);

		if (is_link) {
			char target[4000];
			ssize_t len = readlink(entries[i].name, target, sizeof(target) - 1);
			if (len != -1)
				target[len] = '\0';
			ft_printf(" -> %s", target);
		}
		ft_printf("\n");
	}
	return dir;
}

static char	**display_entries(t_entry *entries, size_t count, t_param *param) {
	int start = 0, end = count, step = 1;
	size_t size_width;
	char	**dir = NULL;

	if (param->r_opt) {
		start = (int)count - 1;
		end = -1;
		step = -1;
	}

	if (param->l_opt) {
		size_width = max_size_width(entries, count);
		size_t link_width = max_link_width(entries, count);
		dir = display_long_entry(start, end, step, entries, size_width, link_width, false);
	}
	else {
		for (int i = start; i != end; i += step) {
			if (S_ISDIR(entries[i].entry_info.st_mode)) {
				ft_printf(BLD_BLUE"%s  "RESET, entries[i].name);
				dir = push_back_path(dir, entries[i].name);
			}
			else
				ft_printf(BLD_WHITE"%s  "RESET, entries[i].name);
		}
		ft_printf("\n");
	}
	return dir;
}

static void free_entries(t_entry *entries, size_t count)
{
	for (size_t i = 0; i < count; i++)
		free(entries[i].name);
	free(entries);
}

static bool	is_dot_entry(const char *name)
{
	return (name && name[0] == '.'
		&& (name[1] == '\0' || (name[1] == '.' && name[2] == '\0')));
}

static void	handle_file(int path_count, char **path_tab, t_param *params) {
	t_entry *files = malloc(sizeof(t_entry) * path_count);
	if (!files) {
		print_error("malloc failed\n");
		return;
	}

	struct	stat stats;
	size_t	files_count = 0;

	for (int i = 0; i < path_count; i++) {
		if (lstat(path_tab[i], &stats) != 0) {
			print_error("lstat failed\n");
			continue;
		}

		if (!S_ISDIR(stats.st_mode)) {
			files[files_count].name = ft_strdup(path_tab[i]);
			if (files[files_count].name) {
				ft_memcpy(&files[files_count].entry_info, &stats, sizeof(struct stat));
				files_count++;
			}
		}
	}
	if (files_count > 0) {
		if (params->t_opt)
			sort_by_time(files, files_count);
		else
			sort_entries(files, files_count);
	}

	int		start = 0, end = files_count, step = 1;

	if (params->r_opt) {
		start = (int)files_count - 1;
		end = -1;
		step = -1;
	}

	if (files_count > 0) {
		if (params->l_opt) {
			size_t size_width = max_size_width(files, files_count);
			size_t link_width = max_link_width(files, files_count);
			display_long_entry(start, end, step, files, size_width, link_width, true);
		}
		else {
			for (int i = start; i != end; i += step) {
				if (S_ISDIR(files[i].entry_info.st_mode))
					ft_printf(BLD_BLUE"%s  "RESET, files[i].name);
				else
					ft_printf(BLD_WHITE"%s  "RESET, files[i].name);
			}
			ft_printf("\n");
		}
	}

	for (size_t i = 0; i < files_count; i++)
		free(files[i].name);
	free(files);
}

static void	handle_dir(char *path, t_param *params, bool multi_dir) {
	DIR *dir = opendir(path);
	if (!dir) {
		print_error("opendir failed\n");
		return;
	}

	size_t count = 0;
	t_entry *entries = load_entries(dir, path, params, &count);
	closedir(dir);

	if (!entries) {
		print_error("malloc failed\n");
		return;
	}

	if (params->t_opt)
		sort_by_time(entries, count);
	else
		sort_entries(entries, count);

	if(multi_dir > 0 || params->R_opt)
		ft_printf("\n%s:\n", path);

	char	**recursive = display_entries(entries, count, params);
	if (params->R_opt && recursive) {
		for (size_t i = 0; recursive[i]; i++) {
			if (is_dot_entry(recursive[i]))
				continue;
			char	*tmp_path = ft_strjoin(path, "/");
			char	*full_path = ft_strjoin(tmp_path, recursive[i]);
			free(tmp_path);
			handle_dir(full_path, params, multi_dir);
			free(full_path);
		}
	}
	free_split(recursive);
	free_entries(entries, count);
}

void listing(t_param *params) {
	char		**path_tab = params->path;
	int			path_count = tab_len(path_tab);
	struct stat	stats;
	int			start = 0, end = path_count, step = 1;

	handle_file(path_count, path_tab, params);

	bool multi_dir = path_count > 1 ? true : false;
	if (params->r_opt) {
		start = path_count - 1;
		end = -1;
		step = -1;
	}

	for (int i = start; i != end; i += step) {
		if (lstat(path_tab[i], &stats) != 0)
			continue;
		if (!S_ISDIR(stats.st_mode))
			continue;
		handle_dir(path_tab[i], params, multi_dir);
	}
}