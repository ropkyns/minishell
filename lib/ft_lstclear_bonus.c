/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:17:20 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/28 18:13:43 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lcpy;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		lcpy = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = lcpy;
	}
	free(*lst);
	*lst = NULL;
}
