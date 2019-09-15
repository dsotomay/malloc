/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:41:45 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/14 21:08:25 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	blk_push(t_zone *lst, size_t size)
{
	void	*curr;
	
	if (!lst->root)
	{
		curr = (void*)lst;
		curr += sizeof(t_zone);
		lst->root = blk_init(curr, size + BLK_SIZE);
		lst->end = lst->root;
	}
	else
	{
		curr = (void*)lst->end;
		curr += (lst->end->blk_size);
		lst->end->next = blk_init(curr, size + BLK_SIZE);
		lst->end = lst->end->next;
	}
}

void	blk_join(t_block *blk1, t_block *blk2)
{
	blk1->blk_size += blk2->blk_size;
	blk1->next = blk2->next;
	blk2->is_free = NULL;
	blk2->blk_size = NULL;
	blk2 = NULL;
}

// void	split_blk(t_block *blk, size_t size) may or may not get used
// {}
