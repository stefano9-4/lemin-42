/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:51:42 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/07 13:00:03 by spozzi           ###   ########.fr       */
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
	//total nb of ants
	int		ants;

	int		num_nodes;
	int		num_edges;
	int		max_paths;

	int		**paths;
	int		**edge_list;
	int		curr_path;
	int		curr_edg;
	// dim 0: a to b
	// dim 1: b to a
	// dim 2: weight
	int		*graph;
	char	*id;

	int		*coor;

	//start and end
	int		src;
	int		snk;
	//int		*dist;
	//int		*prev;
	int		*q;
	int		i;
	int		j;
	int		k;
	int		len;

	t_table	*hm;
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
void	bellmanFord(t_struct *u);
void	print_path(t_struct *u, char *str);
int		*get_BF_path(t_struct *u);
void	suurballe(t_struct *u);
void	find_max_paths(t_struct *u);
int		is_snk_src_connected(t_struct *u);

#endif
