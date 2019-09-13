/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:56:29 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/12 23:42:53 by dysotoma         ###   ########.fr       */
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
	while (i < MIN_ALLOC * 2)
	{
		if (i < MIN_ALLOC / 2)
			blk_push(g_bin.small_lst, 1025);
		else if (i < MIN_ALLOC)
			blk_push(g_bin.small_lst, 2048);
		else if (i < (MIN_ALLOC * 2) - (MIN_ALLOC / 2))
			blk_push(g_bin.tiny_lst, 512);
		else if (i < MIN_ALLOC * 2)
			blk_push(g_bin.tiny_lst, 1024);
		i++;
	}
	g_bin.total = g_bin.small_lst->size + g_bin.tiny_lst->size;
	g_bin.used = g_bin.small_lst->used + g_bin.tiny_lst->used;
	printf("fourth | %i\n", i);
}

t_zone	*zone_init(size_t size)
{
	t_zone	*zone;

	if ((zone = (t_zone*)mmap(NULL, size, (PROT_READ | PROT_WRITE),
	(MAP_PRIVATE | MAP_ANONYMOUS), -1, 0)) == MAP_FAILED)
	{
		ft_errprintf("ERROR: no memory");
		return (MAP_FAILED);
	}
	zone->next = NULL;
	zone->root = NULL;
	zone->end = NULL;
	zone->size = size;
	zone->used = sizeof(t_zone);
	return (zone);
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
