/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:45:46 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/26 09:41:10 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

// verifie la presence d'un \n et retourne un booleen
int	if_newline(t_list_g *reserve)
{
	t_list_g	*current;
	int		i;

	i = 0;
	if (!reserve)
		return (0);
	current = ft_lstlast_g(reserve);
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

// parcourt ma liste et va au dernier maillon
t_list_g	*ft_lstlast_g(t_list_g *reserve)
{
	t_list_g	*current;

	current = reserve;
	while (current && current->next)
		current = current->next;
	return (current);
}

// parcours les noeuds jusqu'a un \n et malloc la ligne 
//avec la taille de la ligne
void	make_line(t_list_g *reserve, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (reserve)
	{
		i = 0;
		while (reserve->content[i])
		{
			if (reserve->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		reserve = reserve->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

// free la reserve
void	free_reserve(t_list_g *reserve)
{
	t_list_g	*current;
	t_list_g	*next;

	current = reserve;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}