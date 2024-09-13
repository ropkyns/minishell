/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:52:28 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/30 14:32:37 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lcpy;
	t_list	*ccpy;

	lcpy = NULL;
	ccpy = NULL;
	while (lst)
	{
		ccpy = ft_lstnew(f(lst->content));
		if (ccpy == NULL)
		{
			if (del)
				del(lst->content);
			ft_lstclear(&lcpy, del);
			return (NULL);
		}
		ft_lstadd_back(&lcpy, ccpy);
		lst = lst->next;
	}
	return (lcpy);
}
