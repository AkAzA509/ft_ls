/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:23:13 by ggirault          #+#    #+#             */
/*   Updated: 2024/11/07 10:20:44 by ggirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	copy_newlst(t_list **new_lst, t_list *new, t_list **last)
{
	if (!*new_lst)
		*new_lst = new;
	else
		(*last)->next = new;
	*last = new;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new;
	t_list	*last;
	void	*new_content;

	new_lst = NULL;
	last = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		new = malloc(sizeof(t_list));
		if (!new)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		new->content = new_content;
		new->next = NULL;
		copy_newlst(&new_lst, new, &last);
		lst = lst->next;
	}
	return (new_lst);
}
