/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:50:28 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/04 13:54:33 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t len)
{
	const unsigned char	*s1;
	const unsigned char	*s2;
	size_t				i;

	i = 0;
	s1 = (const unsigned char *)str1;
	s2 = (const unsigned char *)str2;
	if (len == 0)
		return (0);
	while (i < len)
	{
		if (s1[i] != s2[i])
			return ((int)(s1[i] - s2[i]));
		i++;
	}
	return (0);
}
