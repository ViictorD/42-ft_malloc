/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 12:32:59 by bdurst            #+#    #+#             */
/*   Updated: 2017/10/11 13:40:22 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*strf;
	size_t	i;

	i = 0;
	if (s)
	{
		strf = (char*)malloc(sizeof(char) * (len + 1));
		if (strf)
		{
			while (i < len && start < ft_strlen(s))
			{
				strf[i] = s[start];
				start++;
				i++;
			}
			strf[i] = '\0';
			return (strf);
		}
	}
	return (NULL);
}
