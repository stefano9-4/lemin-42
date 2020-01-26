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
# include <stdbool.h> 
# include "../includes/libft/libft.h"
# include "../includes/libft/get_next_line.h"
# include <stdio.h>

typedef struct s_cons
{
	char 			*name;
	int 			count;
	struct s_cons	*next;
}				t_cons;

typedef struct s_node
{
	//index node
	int cnt;
	//coordinates
	int x;
	int y;
	//name of the node
	char *name;

	//maybe
	//how many connection a node has
	int nb_connections;
	//connections to other nodes
	char **connected_to;
	//temporary number (to use instead of the name ????)
	//double tmp_id; //need to figure out how to generate it
	
	//next element
	struct s_node	*next;
	t_cons	*links;

}				t_node;

// typedef struct  s_lemlist
// {
// 	//??????????????????maybe
// 	int 				info;
// 	//node that contains parsed infos
// 	t_node				node;
// 	///table of value for the node ????
// 	char				**data;
// 	//link to the next one
// 	struct s_lemlist 	*next;
// 	//link to the previous one ???
// 	struct s_lemlist	*previous;

// }				t_lemlist;

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
	t_node	*first;

	int 	info;
	t_node 	*node;
	//t_lemlist	*lemlist;
}				t_struct;

int		parse(char *av, t_struct *u);
int		set_dimentions(char *av, t_struct *u);
int		get_offset_2d(t_struct *u, int x, int y);
int		has_space(char *str);
void	print_graph(t_struct *u);
void	set_zeros(t_struct *u, int size);

#endif
