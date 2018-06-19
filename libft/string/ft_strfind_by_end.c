/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind_by_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 13:39:30 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/10/11 13:39:57 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int		ft_strfind_by_end(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i > 0 && s[i] != c)
		--i;
	return (i);
}
