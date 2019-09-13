/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:37:46 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/12 16:57:45 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

// test code to be removed

struct block_meta {
	size_t size;
	struct block_meta *next;
	int free;
	int magic; // For debugging only. TODO: remove this in non-debug mode.
};

#define META_SIZE sizeof(struct block_meta)
void *global_base = NULL;

struct block_meta *find_free_block(struct block_meta **last, size_t size) {
	struct block_meta *current = global_base;
	while (current && !(current->free && current->size >= size)) {
		*last = current;
		current = current->next;
	}
	return current;
}

struct block_meta *request_space(struct block_meta* last, size_t size) {
	struct block_meta *block;
	block = ft_sbrk(0);
	void *request = ft_sbrk(size + META_SIZE);
	assert((void*)block == request); // Not thread safe.
	if (block == (void*) -1) {
		return NULL; // sbrk failed.
	}
	if (last) { // NULL on first request.
		last->next = block;
	}
	block->size = size;
	block->next = NULL;
	block->free = 0;
	block->magic = 0x12345678;
	return block;
}

void *malloc(size_t size) {
	struct block_meta *block;

	if (size <= 0) {
		return NULL;
	}
	if (!global_base) { // First call.
		block = request_space(NULL, size);
		if (!block) {
			return NULL;
	}
	global_base = block;
	} else {
	struct block_meta *last = global_base;
	block = find_free_block(&last, size);
	if (!block) { // Failed to find free block.
		block = request_space(last, size);
		if (!block) {
			return NULL;
			}
		} else {      // Found free block
		// TODO: consider splitting block here.
		block->free = 0;
		}
	}
	printf("%p | %p | %i\n", block, block+1, sizeof(struct block_meta));
  return(block+1);
}

void free(void *ptr) {
  if (!ptr) {
    return;
  }
  // TODO: consider merging blocks once splitting blocks is implemented.
  struct block_meta* block_ptr = (struct block_meta*)ptr-1;
//   assert(block_ptr->free == 0);
  block_ptr->free = 1;
  block_ptr->magic = 0x55555555;
}

void *realloc(void *ptr, size_t size) {
  if (!ptr) {
    // NULL ptr. realloc should act like malloc.
    return malloc(size);
  }

  struct block_meta* block_ptr = (struct block_meta*)ptr-1;
  if (block_ptr->size >= size) {
    // We have enough space. Could free some once we implement split.
    return ptr;
  }

  // Need to really realloc. Malloc new space and free old space.
  // Then copy old data to new space.
  void *new_ptr;
  new_ptr = malloc(size);
  if (!new_ptr) {
    return NULL; // TODO: set errno on failure.
  }
  memcpy(new_ptr, ptr, block_ptr->size);
  free(ptr);
  return new_ptr;
}

void *calloc(size_t nelem, size_t elsize) {
  size_t size = nelem * elsize; // TODO: check for overflow.
  void *ptr = malloc(size);
  memset(ptr, 0, size);
  return ptr;
}

// start of test main

int main()
{
	struct block_meta *new;
	char *str1 = malloc(sizeof(char) * 24);
	char *str2 = malloc(sizeof(char) * 24);
	// str = (char*)mmap(0, psize, PROT_READ | PROT_WRITE,
	// MAP_ANON | MAP_PRIVATE, -1, 0);
	// _MMAP()
	strcat(str2, "hello world!");
	strcat(str1, "hello world!this is going to overwriteksjhdfkgjhs");
	printf("%s, %p\n", str1, str1);
	void *new1 = (void*)str2;
	new = (struct block_meta*)new1 - 1;
	printf("%c\n", (char)new->next);
	printf("%c\n", (char)new->next);
	printf("%s, %p\n", str2, str2);
	printf("%s\n", (char*)new);
	free(str2);
	printf("%s\n", (char*)new);
	// munmap(str, psize);
	// strcpy(str, "hello world!\n");
	// printf("%s", str);
	// printf("%p\n", str);
}

// end of test code to remove

// static t_block *__split_block(t_block *block, size_t size)
// {
// 	t_block	*new;
// 	if (block->blk_size - size > (sizeof(t_block)))
// 	{
// 		new = blk_init(block->blk_size - size - (sizeof(t_block)));
// 		new->next = block->next;
// 		block->next = new;
// 	}
	
// }

// static t_block *find_free(t_zone *zone, size_t size)
// {
// 	while (zone->next)
// 	{
// 		while (zone->root)
// 			if (zone->root->is_free == 1 && zone->root->blk_size >= size)
// 				return (__split_block(zone->root, size) + 1);
// 			else if (zone->root->is_free == 1)
// 	}
// }

// void	*malloc(size_t size)
// {
// 	if (size <= 0)
// 		return (NULL);
// 	if (!g_bin)
// 		g_bin_init();
// 	check free table
// }
