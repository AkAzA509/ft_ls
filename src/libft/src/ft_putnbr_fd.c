/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:50:28 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/04 14:42:27 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <unistd.h>

static int	len_calc_fd(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	convert_num(char *res, int n, int len)
{
	while (len > 0 && n != 0)
	{
		res[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
}

char	*ft_itoa_fd(int n, char *res, int len)
{
	if (n == -2147483648)
	{
		res[0] = '-';
		res[1] = '2';
		n = 147483648;
	}
	else if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	else if (n == 0)
	{
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	convert_num(res + (n < 0), n, len - (n < 0));
	res[len] = '\0';
	return (res);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	int		len;

	len = len_calc_fd(n);
	ft_itoa_fd(n, str, len);
	write(fd, str, len);
}
