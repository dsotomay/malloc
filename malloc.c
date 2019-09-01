/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:37:46 by dysotoma          #+#    #+#             */
/*   Updated: 2019/08/22 17:24:47 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
// #define NULL ((void *)0)
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
	// static int i = 1;
	// static int total = 0;
	// puts("got here first");
  struct block_meta *block;
	// if (last)
	// {
	// 	printf("%lu\n", (sizeof(*block) * i));
	// 	block = (struct block_meta*)((char*)last + (sizeof(*last)*i) + total);
		
	// 	block->size = size;
	// 	block->next = NULL;
	// 	block->free = 0;
	// 	block->magic = 0x12345678;
	// 	i++;
	// 	total += size;
	// 	return block;
	// }
  block = ft_sbrk(0);//mmap(0, size + META_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);//sbrk(0);
  void *request = ft_sbrk(size + META_SIZE);
  assert((void*)block == request); // Not thread safe.
  if (block == (void*) -1) {
    return NULL; // sbrk failed.
  }

  if (last) { // NULL on first request.
	// puts("got here next");
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
  // TODO: align size?

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
	// puts("oh no not here");
      block = request_space(last, size);
      if (!block) {
        return NULL;
      }
    } else {      // Found free block
      // TODO: consider splitting block here.
		// puts("got here after");
      block->free = 0;
      block->magic = 0x77777777;
    }
  }

  return(block+1);
}

struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}

void free(void *ptr) {
  if (!ptr) {
    return;
  }

  // TODO: consider merging blocks once splitting blocks is implemented.
  struct block_meta* block_ptr = get_block_ptr(ptr);
  assert(block_ptr->free == 0);
  assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
  block_ptr->free = 1;
  block_ptr->magic = 0x55555555;
}

void *realloc(void *ptr, size_t size) {
  if (!ptr) {
    // NULL ptr. realloc should act like malloc.
    return malloc(size);
  }

  struct block_meta* block_ptr = get_block_ptr(ptr);
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
	struct block_meta new;
	char *str1 = malloc(sizeof(char) * 13);
	char *str2 = malloc(sizeof(char) * 13);
	// str = (char*)mmap(0, psize, PROT_READ | PROT_WRITE,
	// MAP_ANON | MAP_PRIVATE, -1, 0);
	// _MMAP()
	strcat(str2, "hello world!");
	strcat(str1, "hello world!this");
	printf("%s, %p\n", str1, str1);
	printf("%s, %p\n", str2, str2);
	// munmap(str, psize);
	// strcpy(str, "hello world!\n");
	// printf("%s", str);
	// printf("%p\n", str);
}

// end of test code to remove





// void	*malloc(size_t size)
// {
	// malloc_introspection_t new;

	// new.discharge()
	// daemon()
// }
