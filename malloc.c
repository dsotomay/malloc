/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:37:46 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/30 01:18:09 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>

// test code to be removed

// void *malloc(size_t size) {
// 	struct block_meta *block;

// 	if (size <= 0) {
// 		return NULL;
// 	}
// 	if (!global_base) { // First call.
// 		block = request_space(NULL, size);
// 		if (!block) {
// 			return NULL;
// 	}
// 	global_base = block;
// 	} else {
// 	struct block_meta *last = global_base;
// 	block = find_free_block(&last, size);
// 	if (!block) { // Failed to find free block.
// 		block = request_space(last, size);
// 		if (!block) {
// 			return NULL;
// 			}
// 		} else {      // Found free block
// 		// TODO: consider splitting block here.
// 		block->free = 0;
// 		}
// 	}
// 	// printf("%p | %p | %i\n", block, block+1, sizeof(struct block_meta));
//   return(block+1);
// }

// start of test main

// int main()
// {
// 	char *str1[1000];
// 	// struct block_meta *new;
// 	for (int i = 0; i < 1000; i++)
// 		str1[i] = malloc(sizeof(char) * 1000);
// 	char *str2 = malloc(sizeof(char) * 13);
// 	// char *str2 = malloc(sizeof(char) * 24);
// 	// str = (char*)mmap(0, psize, PROT_READ | PROT_WRITE,
// 	// MAP_ANON | MAP_PRIVATE, -1, 0);
// 	// _MMAP()
// 	strcat(str2, "hello world!");
// 	// printf("%s, %p\n", str2, str2);
// 	strcat(str1[0], "hello world!this is going to overwriteksjhdfkgjhs");
// 	printf("%s, %p\n", str1[0], (t_block*)str1[0] - 1);
// 	free(str1[0]);
// 	str1[0] = malloc(sizeof(char) * 1000);
// 	// printf("%s, %p\n", str1[0], (t_block*)str1[0] - 1);
// 	// printf("%s, %p\n", str1[0], str1[0]);
// 	// strcat(str1[99], "hello world!this is going to overwriteksjhdfkgjhs");
// 	// printf("%p\n", (((t_block*)str1[99])-1));
// 	show_alloc_mem();
// 	// void *new1 = (void*)str2;
// 	// new = (struct block_meta*)new1 - 1;
// 	// printf("%c\n", (char)new->next);
// 	// printf("%c\n", (char)new->next);
// 	// printf("%s\n", (char*)new);
// 	// free(str2);
// 	// printf("%s\n", (char*)new);
// 	// munmap(str, psize);
// 	// strcpy(str, "hello world!\n");
// 	// printf("%s", str);
// 	// printf("%p\n", str);
// }

// end of test code to remove



/*
** void	de_alloc()
** {
** 	t_zone	*tmp;
** 	while (g_bin.large_lst)
** 	{
** 		tmp = g_bin.large_lst;
** 		g_bin.large_lst = g_bin.large_lst->next;
** 		munmap(tmp, tmp->size);
** 	}
** 	while (g_bin.small_lst)
** 	{
** 		tmp = g_bin.small_lst;
** 		g_bin.small_lst = g_bin.small_lst->next;
** 		munmap(tmp, tmp->size);
** 	}
** 	while (g_bin.tiny_lst)
** 	{
** 		tmp = g_bin.tiny_lst;
** 		g_bin.tiny_lst = g_bin.tiny_lst->next;
** 		munmap(tmp, tmp->size);
** 	}
** 	printf("destructor called\n");
** }
*/
/*
** static t_block *join_blk_check(t_block *block, size_t size)
** {
** 	t_block	*new;
** 	
** 	if (block->blk_size - size > (sizeof(t_block)))
** 	{
** 		new = blk_init(block->blk_size - size - (sizeof(t_block)));
** 		new->next = block->next;
** 		block->next = new;
** 	}
** }
*/

void			*malloc(size_t size)
{
	// static int	is_init = 0;
	t_block		*blk;
	
	// if (!is_init && (is_init = 1))
	// 	g_bin_init();
	// ft_printf("here\n");
	// write(1, "here\n", 5);
	blk = NULL;
	if (size <= 0 || size == ~(0ULL) || size >= g_bin.rlp.rlim_cur)
		return (NULL);
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
	
	return (blk + 1);
}

void			*realloc(void *ptr, size_t size)
{
	void	*new;
	
	if (!ptr)
		return (malloc(size));
	if (((t_block*)ptr - 1)->blk_size - BLK_SIZE >= size)
		return (ptr);
	if (size == 0 && ptr)
	{
		free(ptr);
		return (malloc(TINY));
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

	if (!ptr)
		return ;
	blk = ((t_block*)ptr) - 1;
	blk->is_free = 1;
}

void			*calloc(size_t count, size_t size)
{
	void	*new;
	
	if (!(new = malloc(count * size)))
		return (NULL);
	ft_memset(new, 0, count * size);
	return (new);
}
