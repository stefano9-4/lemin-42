/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:51:42 by spozzi            #+#    #+#             */
/*   Updated: 2020/01/27 15:18:55 by spozzi           ###   ########.fr       */
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
# include <stdbool.h>
# include "../includes/libft/libft.h"
# include "../includes/libft/get_next_line.h"
# include <stdio.h>

typedef	struct	s_node
{
	int				key;
	char			*name;
	int				has_ant;
	int				prev;
	int				isVisited;
	struct s_node	*next;
}				t_node;

typedef	struct 	s_table
{
	int		size;
	t_node	**list;
}				t_table;

typedef struct	s_struct
{
	int		fd;

	//index of elem for chained list
	int 	index;
	//total nb of ants
	int		ants;
	//mark if start/end parsed, if 0, invalid map
	bool	start;
	bool	end;
	//if end or start have only 1 connection, value = 0 else 1
	bool	multi_sol;
	//current direction to optimise
	int 	direction;

	char 	*t_name1;
	char	*t_name2;
	int		num_nodes;

	// dim 0: a to b
	// dim 1: b to a
	// dim 2: weight
	int		*graph;
	char	*id;
	t_table	*hm;
	int		*coor;
	int		src;
	int		snk;
	int		*dist;
	int		*prev;
	int		*q;
	int		i;
	int		j;
	int		k;
	int		len;
	int		v;

	int 	info;
}				t_struct;

int		parse(char *av, t_struct *u);
int		set_dimentions(char *av, t_struct *u);
int		get_offset_2d(t_struct *u, int x, int y);
int		has_space(char *str);
void	print_graph(t_struct *u);
void	set_zeros(t_struct *u, int size);
char	*hm_lookup(t_table *t, int key);
void	hm_insert(t_table *t, int key, char *name);
t_table	*createHashMap(int size);
void	print_stuff(t_struct *u);
int		hashCode(t_table *t, int key);
void	bfs(t_struct *u);

#endif
