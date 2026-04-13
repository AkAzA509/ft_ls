/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:22:34 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/20 15:22:34 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_vfprintf_internal(int fd, const char *str, va_list ap);
int		flag_checker(const char *str, int i);
int		ft_putchar(int fd, char c);
int		s_format(int fd, char *str);
int		x_format(int fd, unsigned long adr, char format, int flag);
int		p_format(int fd, void *adr, char format);
int		convert_hexa(int fd, unsigned long nb, char format);
int		di_format(int fd, int nb, int flag);
int		u_format(int fd, unsigned int nb);
int		zu_format(int fd, size_t nb);
int		zdi_format(int fd, ssize_t nb, int flag);

#endif
