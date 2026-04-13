/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:50:28 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/07 09:25:37 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*str_alloc(const char *str, int len)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[len] = '\0';
	return (tmp);
}

static int	count_substr(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static void	split_strings(char **tab, const char *s, char c)
{
	const char	*start;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		start = &s[i];
		while (s[i] && s[i] != c)
			i++;
		tab[j] = str_alloc(start, s + i - start);
		if (!tab[j])
		{
			free_split(tab);
			return ;
		}
		j++;
	}
	tab[j] = NULL;
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		count;

	if (!s)
		return (NULL);
	count = count_substr(s, c);
	tab = malloc((count + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	split_strings(tab, s, c);
	return (tab);
}
