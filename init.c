/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:56:29 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/12 20:43:09 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	g_bin_init()
{
	int i;
	
	g_bin.pgsize = getpagesize();
	g_bin.large_lst = NULL;
	g_bin.small_lst = zone_init(g_bin.pgsize * 60);
	g_bin.tiny_lst = zone_init(g_bin.pgsize * 25);
	i = 0;
	while (i++ <= MIN_ALLOC / 2)
		blk_push(g_bin.small_lst, 1025);
	while (i++ <= MIN_ALLOC)
		blk_push(g_bin.small_lst, 2048);
	while (i++ <= (MIN_ALLOC * 2) - (MIN_ALLOC / 2))
		blk_push(g_bin.small_lst, 512);
	while (i++ <= MIN_ALLOC * 2)
		blk_push(g_bin.small_lst, 1024);
	g_bin.total = g_bin.small_lst->size + g_bin.tiny_lst->size;
	g_bin.used = g_bin.small_lst->used + g_bin.tiny_lst->used;
}

t_zone	*zone_init(size_t size)
{
	t_zone	*zone;

	if ((zone = (char*)mmap(NULL, size, (PROT_READ | PROT_WRITE),
	(MAP_PRIVATE | MAP_ANONYMOUS), -1, 0)) == MAP_FAILED)
	{
		ft_errprintf("ERROR: no memory");
		return (MAP_FAILED);
	}
	zone->next = NULL;
	zone->root = (t_block*)zone + 1;
	zone->root = NULL;
	zone->size = size;
	zone->size = 0;
	return (zone);
}

t_block	*blk_init(t_block *blk, size_t size)
{
	t_block *new;

	if (!blk)
		new = blk;
	else
		new = blk->next;
	new->blk_size = size;
	new->is_free = 1;
	new->next = NULL;
	return (blk);
}
