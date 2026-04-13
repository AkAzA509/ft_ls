/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/11/17 17:50:29 by marvin            #+#    #+#             */
/*   Updated: 2024/11/17 17:50:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_fprintf.h"
#include "../../include/ft_printf.h"

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list	ap;
	int		total_len;

	va_start(ap, str);
	total_len = ft_vfprintf_internal(fd, str, ap);
	va_end(ap);
	return (total_len);
}