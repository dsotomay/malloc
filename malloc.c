/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:37:46 by dysotoma          #+#    #+#             */
/*   Updated: 2019/10/07 00:25:09 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_bin			g_bin = {
	NULL,
	NULL,
	NULL,
	{0, 0},
	0,
	0,
	0,
	0,
};

/*
** ft_putstr("malloc called ");
** ft_putstr(ft_itoa_base((int64_t)(size),10));
** ft_putstr(" returning 0x");
** ft_putendl(ft_itoa_base((int64_t)(blk + 1), 16));
*/

void			*malloc(size_t size)
{
	t_block		*blk;

	if (!DO_ONCE(g_bin.do_init))
		g_bin_init(&g_bin);
	blk = NULL;
	if ((int64_t)size < 0 || size == ~(0ULL) || size >= g_bin.rlp.rlim_cur)
		return (NULL);
	if (size == 0 || size < 8)
		size = (TINY / 8);
	if (size > SMALL)
	{
		if (!g_bin.large_lst)
			g_bin.large_lst = zone_init(size + sizeof(t_zone) + BLK_SIZE);
		blk = find_free(g_bin.large_lst, size);
	}
	else if (size > TINY)
		blk = find_free(g_bin.small_lst, size);
	else
		blk = find_free(g_bin.tiny_lst, size);
	blk->is_free = 0;
	return (!blk ? blk : blk + 1);
}

void			*realloc(void *ptr, size_t size)
{
	void	*new;

	if (!DO_ONCE(g_bin.do_init))
		g_bin_init(&g_bin);
	if (!ptr)
		return (malloc(size));
	if (!is_mine((t_block*)ptr - 1))
		return (NULL);
	if (((t_block*)ptr - 1)->blk_size - BLK_SIZE >= size)
		return (ptr);
	if (size == 0 && ptr)
	{
		free(ptr);
		return (malloc(size));
	}
	if ((new = malloc(size)) == NULL)
	{
		free(ptr);
		return (new);
	}
	ft_memcpy(new, ptr, ((t_block*)ptr - 1)->blk_size);
	free(ptr);
	return (new);
}

void			free(void *ptr)
{
	t_block *blk;

	if (!DO_ONCE(g_bin.do_init))
		g_bin_init(&g_bin);
	if (!ptr || !is_mine((t_block*)ptr - 1))
		return ;
	blk = ((t_block*)ptr) - 1;
	blk->is_free = 1;
}

/*
** void			*calloc(size_t count, size_t size)
** {
** 	size_t	r_size;
** 	void	*new;
**
** 	if (__builtin_mul_overflow(count, size, &r_size))
** 		return (NULL);
** 	if (!DO_ONCE(g_bin.do_init))
** 		g_bin_init(&g_bin);
** 	if (!(new = ft_memalloc(r_size)))
** 		return (NULL);
** 	// ft_memset(new, 0, count * size);
** 	ft_putstr("calloc called returning 0x");
** 	ft_putendl(ft_itoa_base((int64_t)new, 16));
** 	return (new);
** }
*/
