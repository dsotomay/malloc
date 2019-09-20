/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:46:12 by dysotoma          #+#    #+#             */
/*   Updated: 2019/09/19 23:38:32 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define BLK_SIZE (sizeof(t_block))
# ifndef MIN_ALLOC
#  define MIN_ALLOC 100
# endif
# ifndef TINY
#  define TINY 1024
# endif
# ifndef SMALL
#  define SMALL 4096
# endif
# include <sys/mman.h>
# include "libft/libft.h"

typedef struct	s_block
{
	size_t			blk_size;
	struct s_block	*next;
	int				is_free;
}				t_block;

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
	size_t			total;
	size_t			used;
	int				pgsize;
}				t_bin;

/*
** Global bin struct declared
*/
t_bin			g_bin __attribute__((visibility("hidden")));
void			g_bin_init(void) __attribute__((constructor));
void			de_alloc() __attribute__((destructor));


void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);

/*
** ZONE
*/

t_zone			*zone_init(size_t size);

/*
** BLOCK
*/

t_block			*blk_init(void *blk, size_t size);
void			blk_push(t_zone *lst, size_t size);
t_block			*split_blk(t_block *blk, size_t size);
void			blk_join(t_block *blk1, t_block *blk2);

#endif
