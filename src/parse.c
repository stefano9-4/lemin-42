/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 09:20:06 by lutomasz          #+#    #+#             */
/*   Updated: 2020/01/18 09:20:09 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


t_node		*new_object(void *inf, int id)
{
	t_obj *new;

	if (!(new = (t_obj *)malloc(sizeof(*new))))
		return (NULL);
	new->obj = inf;
	new->id = id;
	new->next = NULL;
	return (new);
}

void		add_object(t_obj **list, t_obj *new)
{
	if (!*list && new)
	{
		*list = new;
		return ;
	}
	if (*list && new)
	{
		new->next = *list;
		*list = new;
	}
}
/*
**	get start node and end node infos !!!to do 
*/

int create_hash_table(t_struct *u)
{
	//create hash table of connections
}

int node_connection(char *line)
{
	//check the format N-N
	//go through the name list and check if valid ????????
	//format name-name
	int i;
	int x;
	int ptr;

	i =0;
	x = 0;
	while (line[i] != '-')
		i++;
	while (u->obj[x])
	{
			if (strncmp(line, obj[x], i) == 1)
				break ;

	}
	line += i;
	if (*line != '-')
		return (0)
	line++;
	i++;
	ptr = i;
	while (ft_isdigit(line[i]) || ft_isalpha(line[i]))
		i++;
	while (u->obj[x])
	{
			if (strncmp(line, obj[x], i - ptr) == 1)
				return (1);
	}
	return (0);
}

void add_node(t_struct *u /*+ node*/)
{
	//add the node in param to the linked list
}

void create_node(char *line, t_struct *u)
{
	//save data in the struct and add it to node list
	int i;

	i = 0;
	///check the format %sname %d %d is correct
	while (ft_isspace(line))
		line++;
	while (ft_isdigit(line) || ft_isalpha(line))
		i++;
	u->node->name = ft_strndup(line);
	line += i;
	while (ft_isspace(line))
		line++;
	u->node->x = ft_atoi(line);
	while (ft_isdigit(line))
		line++;
	u->node->y = ft_atoi(line);
	return (1);
}

//should do additional checks for validity ?????

int check_node(char *line, t_struct *u)
{
	int i;

	i = 0;
	///check the format %sname %d %d is correct
	while (ft_isspace(line))
		line++;
	while (ft_isdigit(line) || ft_isalpha(line))
		i++;
	u->node->name = ft_strndup(line);
	line += i;
	while (ft_isspace(line))
		line++;
	u->node->x = ft_atoi(line);
	while (ft_isdigit(line))
		line++;
	u->node->y = ft_atoi(line);
	return (1);
}


//has to create an elem + add to the list
int start_or_end(char *line, t_struct *u)
{
	t_node	node;

	if (u->start == 1 && u->end == 1)
		ft_putstr("too many edges, error!\n");
	else if (ft_strcmp(line + 2, "start") && u->start = 0)
	{
		printf("parse start\n");
		create_node(u, node);
		u->start = 1;
	}

	else if (ft_strcmp(line + 2, "end") && u->end = 0)
	{
		printf("parse end\n");
		create_node(u, node);
		u->end = 1;
	}
	else
		ft_putstr("START END FORMAT ERROR\n");
	return (0);
}

int parse(char *argv, t_struct *u)
{
	int i;
	char *line;

	get_next_line(u->fd, &line);
	while (!ft_isdigit(line[0]))
	{
		free(line);
		get_next_line(u->fd, &line);
	}
	u->ants = ft_atoi(line);
	printf("%d\n", u->ants);
	free(line);
	while (get_next_line(u->fd, &line))
	{
		if (line[0] == '#')
			if (line[1] == '#')
				start_or_end(line, u);
		else
		{
			if (check_node(line, u))
			{
				create_node(u);
				add_node(u);
			}
			else if (node_connection(u))
			{
					create_hash_table(u);
					add_to_list(u);
					free(line);
			}
			else
				break ;
		} 
	}
	while (get_next_line(u->fd, &line))
	{
		if (line[0] == '#')
			free(line);
		else
		{
			if (connection_format(u))
				add_to_hash(u);
			free(line);
		}
	}
	return (1);
}
