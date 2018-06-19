/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 15:12:39 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/06/19 19:22:37 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	remove_extra(t_block *b)
{
	ft_bzero((void*)b + BLOCK_SIZE, b->size);
	munmap((void*)b + BLOCK_SIZE, b->size);
	b->size = 0;
	b->is_free = 1;
}

static char	try_free(t_block *zone, void *ptr, void *zone_end)
{
	t_block	*b;

	if (!(b = find_ptr(zone, ptr)))
		return (0);
	if (b->is_free)
		return (1);
	if (ptr > (void*)zone && ptr < zone_end &&
		(void*)b->next > (void*)zone && (void*)b->next < zone_end)
	{
		b->is_free = 1;
		ft_bzero((void*)b + BLOCK_SIZE, b->size);
		fusion_block(b);
	}
	else
		remove_extra(b);
	return (1);
}

static void	try_free_large(t_block *b, void *ptr)
{
	t_block	*last;
	size_t	del;

	last = b;
	while (b)
	{
		if ((void*)b + BLOCK_SIZE == ptr)
		{
			if (b == last)
			{
				get_chunks()->large = b->next;
				del = b->size + BLOCK_SIZE;
				ft_bzero((void*)b, del);
				munmap((void*)b, del);
				return ;
			}
			last->next = b->next;
			del = BLOCK_SIZE + b->size;
			ft_bzero((void*)b, del);
			munmap((void*)b, del);
			return ;
		}
		last = b;
		b = b->next;
	}
}

void		fusion_block(t_block *b)
{
	while (b->next && b->next->is_free && \
		(void*)b + BLOCK_SIZE + b->size == b->next)
	{
		b->size += BLOCK_SIZE + b->next->size;
		b->next = b->next->next;
		ft_bzero((void*)b + BLOCK_SIZE + b->size, BLOCK_SIZE);
	}
}

void		free(void *ptr)
{
	if (ptr == NULL)
		return ;
	pthread_mutex_lock(get_lock());
	if (try_free(get_chunks()->tiny, ptr, \
		(void*)get_chunks()->tiny + TINY_MIN) == 1)
		return ;
	else if (try_free(get_chunks()->small, ptr, \
		(void*)get_chunks()->small + SMALL_MIN) == 1)
		return ;
	else
		try_free_large(get_chunks()->large, ptr);
	pthread_mutex_unlock(get_lock());
}
