/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:46:12 by dysotoma          #+#    #+#             */
/*   Updated: 2019/10/07 01:34:18 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# ifndef MIN_ALLOC
#  define MIN_ALLOC 100
# endif
# ifndef TINY
#  define TINY 64
# endif
# ifndef SMALL
#  define SMALL 256
# endif
# define DO_ONCE(x) (x == 1)
# include <sys/mman.h>
# include <sys/resource.h>
# include "libft/libft.h"

typedef struct	s_block
{
	struct s_block	*next;
	size_t			blk_size;
	int				is_free;
}				t_block;
# define BLK_SIZE (sizeof(t_block))

typedef struct	s_zone
{
	struct s_zone	*next;
	t_block			*root;
	t_block			*end;
	size_t			size;
	size_t			used;
}				t_zone;

/*
** Bin struct to contain pointers to the beginning of each zone
** as well as som basic info about about how much memory is allocated and
** how much is currently being used
*/

typedef struct	s_bin
{
	struct s_zone	*tiny_lst;
	struct s_zone	*small_lst;
	struct s_zone	*large_lst;
	struct rlimit	rlp;
	size_t			total;
	size_t			used;
	int				pgsize;
	int				do_init;
}				t_bin;

/*
** Global bin struct declared
*/

t_bin			g_bin __attribute__((visibility("hidden")));
void			g_bin_init(t_bin *g);

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			*calloc(size_t count, size_t size);

/*
** ZONE
*/

t_zone			*zone_init(size_t size);

/*
** BLOCK
*/

t_block			*blk_init(void *blk, size_t size);
t_block			*split_blk(t_block *blk, size_t size);
void			blk_join(t_block *blk1, t_block *blk2);
void			blk_push(t_zone *lst, size_t size);

/*
** MEM_PRINT
*/

void			show_alloc_mem();

/*
** FIND_FREE
*/

t_block			*find_free(t_zone *zone, size_t size);
int				is_mine(t_block *blk);

#endif
