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

typedef struct s_node;
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
	double tmp_id; //need to figure out how to generate it

}				t_node;

typedef struct  s_lemlist
{
	//??????????????????maybe
	int 				info;
	//node that contains parsed infos
	t_node				node;
	///table of value for the node ????
	char				**data;
	//link to the next one
	struct s_lemlist 	*next;
	//link to the previous one ???
	struct s_lemlist	*previous;

}				t_lemlist;

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
	t_node		*node;
}				t_struct;

int parse(char *av, t_struct *u);

#endif
