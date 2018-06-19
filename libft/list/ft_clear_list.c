/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 12:32:56 by bdurst            #+#    #+#             */
/*   Updated: 2017/10/10 22:10:42 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_clear_list(t_list **list, void (*fct_free)(void *))
{
	t_list	*tmp;

	if (list)
	{
		ft_go_start_list(*list);
		tmp = *list;
		while (tmp)
		{
			if (fct_free)
				(*fct_free)((*list)->data);
			tmp = (*list)->next;
			free(*list);
			*list = tmp;
		}
		*list = NULL;
		free(tmp);
	}
}
