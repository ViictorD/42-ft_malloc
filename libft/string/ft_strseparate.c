/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strseparate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 13:40:06 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/10/11 13:40:06 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "io.h"

static size_t	ft_nb_words(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && s)
	{
		if (s[i] == c)
			i++;
		else
		{
			j++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (j);
}

char			**ft_strseparate(char const *s, char c)
{
	char	**tab;
	size_t	len;
	size_t	len_word;
	size_t	j;

	if (s && (tab = (char **)malloc(sizeof(char *) * (ft_nb_words(s, c) + 1))))
	{
		j = 0;
		len = 0;
		while (s[len])
		{
			while (s[len] == c)
				len++;
			len_word = len;
			while (s[len] && s[len] != c)
				len++;
			if (len > len_word)
				tab[j++] = ft_strsub(s, len_word, len - len_word + 1);
		}
		tab[j] = NULL;
		return ((char **)tab);
	}
	return (NULL);
}
