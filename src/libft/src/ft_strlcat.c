/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:50:28 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/04 13:47:31 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	unsigned int	i;
	unsigned int	a;
	unsigned int	b;

	i = 0;
	a = 0;
	b = 0;
	while (dst[a] != '\0')
		a++;
	while (src[b] != '\0')
		b++;
	if (len <= a)
		return (len + b);
	while (i < len - a - 1 && src[i] != '\0')
	{
		dst[a + i] = src[i];
		i++;
	}
	dst[a + i] = '\0';
	return (a + b);
}
