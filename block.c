/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:41:45 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/23 17:54:07 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	blk_push(t_zone *lst, size_t size)
{
	char	*curr;
	
	if (!lst->root)
	{
		curr = (char*)lst;
		curr += sizeof(t_zone);
		lst->root = blk_init(curr, size + BLK_SIZE);
		lst->end = lst->root;
	}
	else
	{
		curr = (char*)lst->end;
		curr += (lst->end->blk_size);
		lst->end->next = blk_init(curr, size + BLK_SIZE);
		lst->end = lst->end->next;
	}
}

void	blk_join(t_block *blk1, t_block *blk2)
{
	blk1->blk_size += blk2->blk_size;
	blk1->next = blk2->next;
	blk2->is_free = 0;
	blk2->blk_size = 0;
	blk2 = NULL;
}

t_block	*split_blk(t_block *blk, size_t size)
{
	char *blk1;
	t_block *tmp;
	
	tmp = blk->next;
	blk1 = (char*)blk;
	blk1 += (blk->blk_size - (blk->blk_size - size));
	blk->next = blk_init(blk1, blk->blk_size - size);
	((t_block*)blk1)->next = tmp;
	if (blk->next->blk_size - BLK_SIZE < 8 && blk->next->next
	&& blk->next->next->is_free == 1)
		blk_join(blk->next, blk->next->next);
	return (blk);
}
