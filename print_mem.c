/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 19:28:17 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/23 17:54:32 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	print_tiny(t_zone *zone)
{
	static int i = 0;
	ft_printf("\n\nTINY ZONE=======================\n");
				// ft_printf("%i %p\n", zone->root->is_free, zone->root);
	while (zone)
	{
		if (zone->root)
		while (zone->root)
		{
			i++;
			if (!zone->root->is_free)
			{
				ft_printf("pointer at %p has %d allocated\n", zone->root,
				zone->root->blk_size - BLK_SIZE);
			}
			zone->root = zone->root->next;
		}
		zone = zone->next;
	}
	ft_printf("%i\n",i);
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
		ft_printf("tiny_lstp = %p\n", g_bin.tiny_lst);
	if (g_bin.tiny_lst)
	{
		ft_printf("tiny_lst->rootp = %p\n", g_bin.tiny_lst->root);
		print_tiny(g_bin.tiny_lst);
	}
	if (g_bin.small_lst)
		print_small(g_bin.small_lst);
	
}
