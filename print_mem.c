/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 19:28:17 by dysotoma          #+#    #+#             */
/*   Updated: 2019/10/07 00:36:45 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	print_tiny(t_zone *z)
{
	t_zone	*zone;
	t_block	*blk;

	zone = z;
	ft_printf("\n\nTINY ZONE=======================\n");
	while (zone)
	{
		blk = zone->root;
		while (blk)
		{
			if (!blk->is_free)
			{
				ft_printf("pointer at %p has %d allocated\n", blk,
				blk->blk_size - BLK_SIZE);
			}
			blk = blk->next;
		}
		zone = zone->next;
	}
}

static void	print_small(t_zone *z)
{
	t_zone	*zone;
	t_block	*blk;

	zone = z;
	ft_printf("\n\nSMALL ZONE=======================\n");
	while (zone)
	{
		blk = zone->root;
		while (blk)
		{
			if (!blk->is_free)
			{
				ft_printf("pointer at %p has %d allocated\n", blk,
				blk->blk_size - BLK_SIZE);
			}
			blk = blk->next;
		}
		zone = zone->next;
	}
}

static void	print_large(t_zone *z)
{
	t_zone	*zone;
	t_block	*blk;

	zone = z;
	ft_printf("\n\nLARGE ZONE=======================\n");
	while (zone)
	{
		blk = zone->root;
		while (blk)
		{
			if (!blk->is_free)
			{
				ft_printf("pointer at %p has %d allocated\n", blk,
				blk->blk_size - BLK_SIZE);
			}
			blk = blk->next;
		}
		zone = zone->next;
	}
}

void		show_alloc_mem(void)
{
	if (g_bin.tiny_lst)
		print_tiny(g_bin.tiny_lst);
	if (g_bin.small_lst)
		print_small(g_bin.small_lst);
	if (g_bin.large_lst)
		print_large(g_bin.large_lst);
}
