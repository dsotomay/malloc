/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:41:45 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/12 19:01:09 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	blk_push(t_zone *lst, size_t size)
{
	if (!lst->root)
		blk_init(lst->root, size);
	else
		
}

// void	blk_join(t_block *blk1, t_block blk2) may or may not get used
// {}

// void	split_blk(t_block *blk, size_t size) may or may not get used
// {}
