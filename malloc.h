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

typedef struct	s_zone
{
	struct s_zone	*tlst;
	struct s_zone	*slst;
	struct s_zone	*llst;
	size_t			total;
	size->t	
}				t_zone;

void	*g_bin;

void 	*ft_sbrk(size_t size);
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

#endif