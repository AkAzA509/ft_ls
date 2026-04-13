/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:50:28 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/06 15:44:53 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	trimmer(char const *s1, int *start, int *end, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[j] != '\0')
		j++;
	while (s1[i] != '\0' && in_set(s1[i], set) == 1)
		i++;
	*start = i;
	while (j > i && in_set(s1[j - 1], set) == 1)
		j--;
	*end = j;
}

static char	*alloc_empty(void)
{
	char	*res;

	res = malloc(1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start;
	int		end;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	trimmer(s1, &start, &end, set);
	if (start >= end)
		return (alloc_empty());
	res = malloc(end - start + 1);
	if (res == NULL)
		return (NULL);
	while (start < end)
	{
		res[i] = s1[start];
		start++;
		i++;
	}
	res[i] = '\0';
	return (res);
}
