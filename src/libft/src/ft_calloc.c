/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:50:28 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/07 10:37:04 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
//sert a malloc un pointeur pour nb element de taille size octets
void	*ft_calloc(size_t nb, size_t size)
{
	unsigned char			*p;
	void					*ptr;
	size_t					total;
	size_t					i;

	i = 0;
	total = nb * size;
	if (nb != 0 && size != 0 && total / nb != size)
		return (NULL);
	ptr = malloc (total);
	if (ptr == NULL)
		return (NULL);
	p = (unsigned char *)ptr;
	while (i < total)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}
