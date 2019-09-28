/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 19:28:17 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/27 22:27:32 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	print_tiny(t_zone *z)
{
	static int i = 0;
	t_zone	*zone;
	t_block	*blk;

	zone = z;
	ft_printf("\n\nTINY ZONE=======================\n");
				ft_printf("%i %p\n", zone->root->is_free, zone->root);
	while (zone)
	{
		// if (zone->root)
			i++;
		blk = zone->root;
		while (blk && blk->next)
		{
			if (!blk->is_free)
			{
				if (blk->next)
					i++;
				ft_printf("pointer at %p has %d allocated\n", blk,
				blk->blk_size - BLK_SIZE);
				ft_printf("%i\n",i);
			}
			blk = blk->next;
		}
		zone = zone->next;
	ft_printf("%i\n",i);
	}
}

static void	print_small(t_zone *zone)
{
	ft_printf("\n\nSMALL ZONE=======================\n");
	while (zone)
	{
		while (zone->root)
		{
			if (!zone->root->is_free)
				ft_printf("pointer at %p has %d allocated\n", zone->root + 1,
				zone->root->blk_size - BLK_SIZE);
			zone->root = zone->root->next;
		}
		zone = zone->next;
	}
}

void show_alloc_mem()
{
	ft_printf("hello\n");
		ft_printf("tiny_lstp = %p\n", g_bin.tiny_lst->root);
		ft_printf("tiny_lstp = %p\n", g_bin.tiny_lst->end);
	if (g_bin.tiny_lst)
	{
		ft_printf("tiny_lst->rootp = %p\n", g_bin.tiny_lst->root);
		print_tiny(g_bin.tiny_lst);
	}
	if (g_bin.small_lst)
		print_small(g_bin.small_lst);
	
}
