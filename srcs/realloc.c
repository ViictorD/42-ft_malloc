/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 15:12:06 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/06/21 20:10:46 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static t_block	*move_data(t_block *b, void *ptr, size_t size)
{
	void	*new;

	pthread_mutex_unlock(get_lock());
	new = malloc(size);
	ft_memcpy(new, ptr, b->size);
	free(ptr);
	return (new);
}

static t_block	*realloc_less(t_block *b, void *ptr, size_t size)
{
	t_block	*save;

	ft_bzero(ptr + size, b->size - size);
	save = b->next;
	b->next = ptr + size;
	b->next->size = b->size - BLOCK_SIZE - size;
	b->next->is_free = 1;
	b->next->next = save;
	fusion_block(b->next);
	pthread_mutex_unlock(get_lock());
	return (ptr);
}

static t_block	*realloc_tiny_small(t_block *b, void *ptr, size_t size)
{
	size_t	free_size;
	t_block	*save;

	if (size + BLOCK_SIZE < b->size && !b->next->is_free)
		return (realloc_less(b, ptr, size));
	else if (b->next && b->next->is_free && b->next->size + BLOCK_SIZE * 2 + \
		b->size >= size)
	{
		save = b->next->next;
		free_size = b->next->size;
		ft_bzero(b->next, BLOCK_SIZE);
		b->next = (void*)b + BLOCK_SIZE + size;
		b->next->size = b->size + BLOCK_SIZE + free_size - size - BLOCK_SIZE;
		b->next->is_free = 1;
		b->next->next = save;
		b->size = size;
		pthread_mutex_unlock(get_lock());
		return (ptr);
	}
	else if (!b->next || !b->next->is_free)
		return (move_data(b, ptr, size));
	pthread_mutex_unlock(get_lock());
	return (NULL);
}

static void		*realloc_large(t_block *b, void *ptr, size_t size)
{
	if (size == b->size)
		return (ptr);
	else if (size < b->size)
	{
		ft_bzero((void*)b + BLOCK_SIZE + size, b->size - size);
		munmap((void*)b + BLOCK_SIZE + size, b->size - size);
		b->size = size;
		pthread_mutex_unlock(get_lock());
		return (ptr);
	}
	else
		return (move_data(b, ptr, size));
}

void			*realloc(void *ptr, size_t size)
{
	t_block	*b;

	if (!ptr)
		return (malloc(size));
	else if (ptr && size == 0)
	{
		free(ptr);
		return (NULL);
	}
	pthread_mutex_lock(get_lock());
	if ((b = find_ptr(get_chunks()->tiny, ptr)) != NULL ||
		(b = find_ptr(get_chunks()->small, ptr)) != NULL)
	{
		if (size == b->size)
		{
			pthread_mutex_unlock(get_lock());
			return (ptr);
		}
		return (realloc_tiny_small(b, ptr, size));
	}
	else if ((b = find_ptr(get_chunks()->large, ptr)) != NULL)
		return (realloc_large(b, ptr, size));
	pthread_mutex_unlock(get_lock());
	return (NULL);
}
