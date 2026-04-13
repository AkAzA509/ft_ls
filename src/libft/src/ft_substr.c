/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:50:28 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/04 14:21:51 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*alloc_ptr(int num, size_t len)
{
	char	*cpy;

	if (num == 0)
	{
		cpy = malloc(1);
		if (cpy == NULL)
			return (NULL);
		cpy[0] = '\0';
	}
	else
	{
		cpy = malloc(len + 1);
		if (cpy == NULL)
			return (NULL);
	}
	return (cpy);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*cpy;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
		i++;
	if (start >= i)
		return (alloc_ptr(0, len));
	if (len > i - start)
		len = i - start;
	cpy = alloc_ptr(1, len);
	while (j < len)
	{
		cpy[j] = str[start + j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}
