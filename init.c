/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:56:29 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/26 01:19:19 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>

void	g_bin_init()
{
	
	int i;
	
	g_bin.pgsize = getpagesize();
	getrlimit(RLIMIT_DATA, &g_bin.rlp);
	g_bin.large_lst = NULL;
	g_bin.small_lst = zone_init(g_bin.pgsize * 60);
	g_bin.tiny_lst = zone_init(g_bin.pgsize * 25);
	i = 0;
	while (i < MIN_ALLOC * 2)
	{
		if (i < MIN_ALLOC / 2)
			blk_push(g_bin.small_lst, TINY + 1);
		else if (i < MIN_ALLOC)
			blk_push(g_bin.small_lst, SMALL / 2);
		else if (i < (MIN_ALLOC * 2) - (MIN_ALLOC / 2))
			blk_push(g_bin.tiny_lst, TINY / 2);
		else if (i < MIN_ALLOC * 2)
			blk_push(g_bin.tiny_lst, TINY);
		i++;
	}
	ft_printf("start = %p\n", g_bin.tiny_lst);
	g_bin.total = g_bin.small_lst->size + g_bin.tiny_lst->size;
	g_bin.used = g_bin.small_lst->used + g_bin.tiny_lst->used;
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
	t_block *new;

	new = blk;
	new->blk_size = size;
	new->is_free = 1;
	new->next = NULL;
	return (new);
}
