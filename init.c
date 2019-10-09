/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:56:29 by dysotoma          #+#    #+#             */
/*   Updated: 2019/10/07 01:27:40 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>

void	g_bin_init(t_bin *g)
{
	int i;

	g->pgsize = getpagesize();
	getrlimit(RLIMIT_DATA, &g->rlp);
	g->large_lst = NULL;
	g->small_lst = zone_init((SMALL * MIN_ALLOC / g->pgsize + 2) * g->pgsize);
	g->tiny_lst = zone_init((TINY * MIN_ALLOC / g->pgsize + 2) * g->pgsize);
	i = 0;
	while (i < MIN_ALLOC * 2)
	{
		if (i < MIN_ALLOC)
			blk_push(g->tiny_lst, TINY);
		else if (i < MIN_ALLOC * 2)
			blk_push(g->small_lst, SMALL / 2);
		i++;
	}
	g->total = g->small_lst->size + g->tiny_lst->size;
	g->used = g->small_lst->used + g->tiny_lst->used;
	g->do_init = 1;
}

t_zone	*zone_init(size_t size)
{
	char	*zone;

	if ((zone = (char*)mmap(NULL, size, (PROT_READ | PROT_WRITE),
	(MAP_PRIVATE | MAP_ANONYMOUS), -1, 0)) == MAP_FAILED)
	{
		ft_putendl_fd("ERROR: no memory", STDERR_FILENO);
		return (MAP_FAILED);
	}
	((t_zone*)zone)->next = NULL;
	((t_zone*)zone)->root = NULL;
	((t_zone*)zone)->end = NULL;
	((t_zone*)zone)->size = size;
	((t_zone*)zone)->used = sizeof(t_zone);
	return ((t_zone*)zone);
}

t_block	*blk_init(void *blk, size_t size)
{
	char *new;

	new = blk;
	((t_block*)new)->blk_size = size;
	((t_block*)new)->is_free = 1;
	((t_block*)new)->next = NULL;
	return ((t_block*)new);
}
