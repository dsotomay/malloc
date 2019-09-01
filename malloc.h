/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:46:12 by dysotoma          #+#    #+#             */
/*   Updated: 2019/08/22 20:49:46 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <sys/mman.h>

typedef struct	s_block
{
	struct	s_block	*left;
	struct	s_block	*right;
	size_t			blk_size;
	int				is_free;
}				t_block;

typedef struct	s_zone
{
	struct s_zone	*next;
	t_block			*root;
	size_t			size;
	size_t			used;
}				t_zone;


typedef struct	s_bin
{
	struct s_zone	*tiny_lst;
	struct s_zone	*small_lst;
	struct s_zone	*large_lst;
	size_t			total;
	size_t			used;
}				t_bin;

t_bin	*g_bin;

void 	*ft_sbrk(size_t size);
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

/*
** ZONE
*/
TODO: need list traversal
t_zone	*zone_init(size_t size);

/*
** BLOCK
*/
TODO: need tree traversal as well as 
t_block	*blk_init(size_t size);

#endif