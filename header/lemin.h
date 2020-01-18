/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:51:42 by spozzi            #+#    #+#             */
/*   Updated: 2020/01/14 12:43:04 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../includes/libft/libft.h"
# include "../includes/libft/get_next_line.h"
# include <stdio.h>

typedef struct  s_lemlist
{	
	int 				info;
	char				*name;
	char				**data;
	struct s_lemlist 	*next;
	struct s_lemlist	*previous;
	
}				t_lemlist;		

typedef struct	s_struct
{
	int		fd;
	int		ants;

	int		node;
	int		*graph;
	int		src[2];
	int		snk[2];
	int		*dist;
	int		*prev;
	int		*q;
	int		i;
	int		v;
	t_lemlist	*list;
}				t_struct;

int parse(char *av, t_struct *u);

#endif