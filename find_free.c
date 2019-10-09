/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:35:08 by dysotoma          #+#    #+#             */
/*   Updated: 2019/10/07 01:35:21 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int		check_blk(t_zone *zone, t_block *blk)
{
	t_block *nblk;

	while (zone && (int64_t)zone != -1)
	{
		nblk = zone->root;
		while (nblk)
		{
			if (nblk == blk)
				return (1);
			nblk = nblk->next;
		}
		zone = zone->next;
	}
	return (0);
}

int				is_mine(t_block *blk)
{
	t_zone	*zone;
	int		tiny;
	int		small;
	int		large;

	tiny = 0;
	small = 0;
	large = 0;
	while (!tiny || !small || !large)
	{
		if (!tiny && (tiny = 1))
			zone = g_bin.tiny_lst;
		else if (!small && (small = 1))
			zone = g_bin.small_lst;
		else if (!large && (large = 1))
			zone = g_bin.large_lst;
		if (check_blk(zone, blk))
			return (1);
	}
	return (0);
}

static int		need_new_blk(t_zone **zone, size_t size)
{
	size_t	size_chk;

	size_chk = (size_t)(*zone)->end - (size_t)(*zone) + size + BLK_SIZE;
	if ((*zone)->used == sizeof(t_zone) || size_chk <= (*zone)->size)
	{
		blk_push((*zone), size);
		(*zone)->used += (*zone)->end->blk_size;
		return (1);
	}
	return (0);
}

static void		more_space(t_zone **zone, size_t size)
{
	size_t	sz;

	sz = ((size + sizeof(t_zone) + BLK_SIZE) / g_bin.pgsize + 2) * g_bin.pgsize;
	if (!(*zone)->next)
	{
		if (size > SMALL)
			(*zone)->next = zone_init(sz);
		else
			(*zone)->next = zone_init(g_bin.pgsize * 2);
	}
}

t_block			*find_free(t_zone *z, size_t size)
{
	t_zone	*zone;
	t_block	*blk;

	zone = z;
	while (zone)
	{
		blk = zone->root;
		while ((int)blk != -1 && blk)
		{
			if (blk->is_free == 1 && blk->blk_size >= size)
			{
				zone->used += blk->blk_size + BLK_SIZE;
				return (blk);
			}
			blk = (int)blk->next != -1 ? blk->next : NULL;
		}
		if (zone && !blk)
			if (need_new_blk(&zone, size))
				return (zone->end);
		more_space(&zone, size);
		zone = (int)zone->next != -1 ? zone->next : NULL;
	}
	return (NULL);
}
