/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 13:38:09 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/10/11 13:38:33 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_pop_node(t_list **node, void (*fct_free)(void *))
{
	t_list	*tmp;

	if (*node)
	{
		tmp = *node;
		if (tmp->prev)
		{
			*node = tmp->prev;
			tmp->prev->next = tmp->next;
		}
		if (tmp->next)
		{
			*node = tmp->next;
			tmp->next->prev = tmp->prev;
		}
		if (fct_free)
			(*fct_free)(tmp->data);
		free(tmp);
		if (tmp == *node)
			*node = NULL;
		tmp = NULL;
	}
}
