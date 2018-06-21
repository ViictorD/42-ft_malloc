/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 19:52:27 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/06/21 21:05:19 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static size_t	count_block(t_block *b)
{
	size_t	count;

	count = 0;
	while (b)
	{
		++count;
		b = b->next;
	}
	return (count);
}

static void		dump_hex(t_block *b)
{
	size_t	i;
	char	*tmp;

	i = -1;
	while (++i < b->size)
	{
		tmp = ((void*)b + BLOCK_SIZE + i);
		if (tmp[0] < 16)
			ft_putchar('0');
		print_hex((long)tmp[0], 0);
		ft_putchar(' ');
	}
}

static void		print_block_ex(t_block *b, long *total)
{
	total[0] = 0;
	total[1] = 0;
	while (b)
	{
		print_hex((long)(void*)b, 1);
		b->is_free ? ft_putstr(" : free : ") : ft_putstr(" : used : ");
		print_hex((long)((void*)b + BLOCK_SIZE), 1);
		ft_putstr(" - ");
		print_hex((long)((void*)b + BLOCK_SIZE + b->size), 1);
		ft_putstr(" : ");
		print_nb(b->size);
		ft_putendl(" octets");
		if (!b->is_free)
		{
			dump_hex(b);
			ft_putchar('\n');
		}
		if (!b->is_free)
			total[0] += b->size;
		else
			total[1] += b->size;
		b = b->next;
	}
}

void			print_zone(t_block *b, char *str, long *total)
{
	ft_putstr(str);
	print_hex((long)b, 1);
	ft_putstr(" : ");
	pthread_mutex_unlock(get_lock());
	ft_putnbr(count_block(b));
	pthread_mutex_lock(get_lock());
	ft_putendl(" blocks allocated");
	print_block_ex(b, total);
}

void			show_alloc_mem_ex(void)
{
	long	total[2];
	long	tmp[2];

	pthread_mutex_lock(get_lock());
	total[0] = 0;
	total[1] = 0;
	print_zone(get_chunks()->tiny, "TINY : ", tmp);
	total[0] += tmp[0];
	total[1] += tmp[1];
	print_zone(get_chunks()->small, "SMALL : ", tmp);
	total[0] += tmp[0];
	total[1] += tmp[1];
	print_zone(get_chunks()->large, "LARGE : ", tmp);
	total[0] += tmp[0];
	total[1] += tmp[1];
	pthread_mutex_unlock(get_lock());
	ft_putstr("Total free : ");
	print_nb(total[1]);
	ft_putendl(" octets");
	ft_putstr("Total used : ");
	print_nb(total[0]);
	ft_putendl(" octets");
}
