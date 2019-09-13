/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbrk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:07:34 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/07 21:15:23 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX_HEAP 64*1024*4096

char *heap;
char *brkp = NULL;
char *endp = NULL;
static void init() __attribute__ ((constructor));

void init()
{
	
	// g_bin = &
	heap = (char*)mmap(NULL, MAX_HEAP, (PROT_READ | PROT_WRITE),
	(MAP_PRIVATE | MAP_ANONYMOUS), -1, 0);
	brkp = heap;
	endp = brkp + MAX_HEAP;
}

void *ft_sbrk(size_t size)
{
	// t_zone	*zone;

	// zone = (t_zone*)g_bin;
	// zone->
	// puts("got here");
	if (size == 0)
		return (void *)brkp;
	void *free = (void*)brkp;
	brkp += size;
	if (brkp >= endp)
		return NULL;
	// printf("%p\n", free);
	return free;
}
