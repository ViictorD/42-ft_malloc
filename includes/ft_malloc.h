/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:22:05 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/06/19 19:24:45 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>
# include "../libft/libft.h"

# define TINY			256
# define SMALL			4096

# define TINY_MIN		(getpagesize() * 100 * TINY)
# define SMALL_MIN		(getpagesize() * 100 * SMALL)
# define BLOCK_SIZE		sizeof(struct s_block)
# define BLOCK_DATA(b)	(((void*)b + BLOCK_SIZE))
# define ALLIGN4(x)		(((((x) - 1) >> 2) << 2) + 4)

typedef struct		s_block
{
	size_t			size;
	size_t			is_free;
	struct s_block	*next;
}					t_block;

typedef struct		s_chunk
{
	struct s_block	*tiny;
	struct s_block	*small;
	struct s_block	*large;
}					t_chunk;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);
t_chunk				*get_chunks(void);
void				split_block(t_block *b, size_t size);
t_block				*find_ptr(t_block *b, void *ptr);
void				fusion_block(t_block *b);
pthread_mutex_t		*get_lock();

#endif
