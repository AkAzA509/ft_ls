/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:50:28 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/04 13:46:47 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	is_overlap_cpy(size_t len, unsigned char *d, unsigned char *s)
{
	if (d > s && d < s + len)
	{
		d += len - 1;
		s += len - 1;
		while (len > 0)
		{
			*d-- = *s--;
			len--;
		}
		return (1);
	}
	return (0);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (len == 0 || src == NULL || dst == NULL)
		return (dst);
	if (!is_overlap_cpy(len, d, s))
	{
		while (len > 0)
		{
			*d++ = *s++;
			len--;
		}
	}
	return (dst);
}
