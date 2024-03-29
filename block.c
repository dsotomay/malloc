/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:41:45 by dysotoma          #+#    #+#             */
/*   Updated: 2019/10/06 21:11:44 by dysotoma         ###   ########.fr       */
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

/*
** void	blk_join(t_block *blk1, t_block *blk2)
** {
** 	blk1->blk_size += blk2->blk_size;
** 	blk2->blk_size = 0;
** 	blk1->next = blk2->next;
** 	blk2->next = NULL;
** 	blk2->is_free = 0;
** 	blk2 = NULL;
** }
**
** t_block	*split_blk(t_block *blk, size_t size)
** {
** 	char *blk1;
** 	t_block *tmp;
** 	t_block *new;
** 	int bsize;
**
** 	tmp = blk->next;
** 	blk1 = (char*)blk + (blk->blk_size - (blk->blk_size - size));
** 	if ((blk->blk_size - size) > 0)
** 	{
** 		new = blk_init(blk1, blk->blk_size - size);
** 		new->next = tmp;
** 		blk->next = new;
** 		if (blk->next->blk_size - BLK_SIZE < 8 && blk->next->next
** 		&& blk->next->next->is_free == 1)
** 			blk_join(blk->next, blk->next->next);
** 	}
** 	// if (blk->next->blk_size - BLK_SIZE > size - BLK_SIZE && size -
** BLK_SIZE <= TINY)
** 	// 	split_blk(blk->next, TINY / 2);
** 	// else if (blk->next->blk_size > size && size - BLK_SIZE <= SMALL)
** 	// 	split_blk(blk->next, SMALL / 2);
** 	// blk->blk_size = size;
** 	return (blk);
** }
*/
