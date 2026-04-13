/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:45:44 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/27 15:27:35 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_list_g
{
	char			*content;
	struct s_list_g	*next;
}					t_list_g;

char				*get_next_line(int fd);
void				read_and_stock(t_list_g **reserve, int fd);
void				add_to_stock(t_list_g **reserve, char *buf, int readed);
void				find_line(t_list_g *reserve, char **line);
void				clean_reserve(t_list_g **reserve);
int					if_newline(t_list_g *reserve);
t_list_g			*ft_lstlast_g(t_list_g *reserve);
void				make_line(t_list_g *reserve, char **line);
void				free_reserve(t_list_g *reserve);

#endif
