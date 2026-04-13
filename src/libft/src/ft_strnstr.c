/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:50:28 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/04 13:54:58 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (substr[0] == '\0')
		return ((char *)str);
	while (i < len && str[i] != '\0')
	{
		j = 0;
		if (substr[j] == str[i])
		{
			while (substr[j] != '\0' && substr[j] == str[i + j] && i + j < len)
				j++;
			if (substr[j] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
