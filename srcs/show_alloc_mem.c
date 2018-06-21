/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 18:47:59 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/06/21 21:03:33 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static long	print_block(t_block *b)
{
	long	total;

	total = 0;
	while (b && !b->is_free)
	{
		print_hex((long)((void*)b + BLOCK_SIZE), 1);
		ft_putstr(" - ");
		print_hex((long)((void*)b + BLOCK_SIZE + b->size), 1);
		ft_putstr(" : ");
		print_nb(b->size);
		ft_putendl(" octets");
		total += b->size;
		b = b->next;
	}
	return (total);
}

void		print_nb(long nb)
{
	if (nb >= 10)
		print_nb(nb / 10);
	ft_putchar((char)(48 + (nb % 10)));
}

void		print_hex(long nb, char first)
{
	if (first)
		ft_putstr("0x");
	if (nb >= 16)
		print_hex(nb / 16, 0);
	if (nb % 16 < 10)
		ft_putchar((char)(((nb % 16) + 48)));
	else
		ft_putchar((char)((nb % 16) + 55));
}

void		show_alloc_mem(void)
{
	long	total;

	pthread_mutex_lock(get_lock());
	total = 0;
	ft_putstr("TINY : ");
	print_hex((long)(get_chunks()->tiny), 1);
	ft_putchar('\n');
	total += print_block(get_chunks()->tiny);
	ft_putstr("SMALL : ");
	print_hex((long)(get_chunks()->small), 1);
	ft_putchar('\n');
	total += print_block(get_chunks()->small);
	ft_putstr("LARGE : ");
	print_hex((long)(get_chunks()->large), 1);
	ft_putchar('\n');
	total += print_block(get_chunks()->large);
	pthread_mutex_unlock(get_lock());
	ft_putstr("Total : ");
	print_nb(total);
	ft_putendl(" octets");
}
