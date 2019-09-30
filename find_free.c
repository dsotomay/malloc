/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:35:08 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/30 02:08:33 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


// static t_block	*

static void		more_space(t_zone **zone, size_t size)
{
	if (size > SMALL)
		(*zone)->next = zone_init(size + sizeof(t_zone) + BLK_SIZE);
	else			
		(*zone)->next = zone_init(g_bin.pgsize * 25);
}

t_block 		*find_free(t_zone *z, size_t size)
{
	t_zone	*zone;
	t_block	*blk;

	zone = z;
			// ft_printf("zone->rootp = %p\n", *zone);
	while (zone)
	{
		blk = zone->root;
		while ((int)blk != -1 && blk)
		{
			if (blk->is_free == 1 && blk->blk_size >= size)
			{
				zone->used += blk->blk_size + BLK_SIZE;
				return (split_blk(blk, size + BLK_SIZE));
			}
			blk = (int)blk->next != -1 ? blk->next : NULL;
		} // if above fails then i should push a new block until i can't at
		// which point i should check if there is a new zone.
		if (zone && !blk)
			if (zone->used == sizeof(t_zone) || (size_t)zone->end - (size_t)zone + size + BLK_SIZE <= zone->size)
			{
				blk_push(zone, size);
				zone->used += zone->end->blk_size;
				return (zone->end);
			}
		if (!zone->next)
			more_space(&zone, size);
		zone = (int)zone->next != -1 ? zone->next : NULL;
	}
	return (NULL);
}
