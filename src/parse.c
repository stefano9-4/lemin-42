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

void		add_node(t_lemlist **list, t_node *new)
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

int add_node(char *line, t_struct *u)
{
	//check the format N-N
	//go through the name list and check if valid ????????
	//format name-name
	int i;
	int x;
	int ptr;
	t_lemlist *next;

	i = 0;
	while (ft_isdigit(line) || ft_isalpha(line))
		i++;
	x = 0;
	u->t_name1 = ft_strndup(line, i);
	while (u->lemlist->next)
	{
			if (strncmp(line, u->lemlist.node.name, i) == 1)
				break ;
			next = u->lemlist->next;

	}
	line += i;
	if (*line != '-')
		return (0)
	line++;
	i++;
	ptr = i;
	while (ft_isdigit(line[i]) || ft_isalpha(line[i]))
		i++;
	u->t_name2 = ft_strndup(line, i);
	while (u->lemlist->next)
	{
			if (strncmp(line, u->lemlist.node.name, i) == 1)
				return (1);
			next = u->lemlist->next;
	}
	return (0);
}

void add_connection(char *line, t_struct *u /*+ node*/)
{
	t_lemlist *next;

	while (u->lemlist->next)
	{
		if (ft_strcmp(u->t_name1, u->lemlist.node.name) == 1)
		{
				u->lemlist.node.nb_connections++;
				u->lemlist.node.connected_to[u->lemlist.node.nb_connections] = ft_strdup(u->t_name2);
		}
		if (ft_strcmp(u->t_name2, u->lemlist.node.name) == 1)
		{
				u->lemlist.node.nb_connections++;
				u->lemlist.node.connected_to[u->lemlist.node.nb_connections] = ft_strdup(u->t_name1);
		}
		next = u->lemlist->next;
	}
	free(u->t_name1);
	free(u->t_name2);
	//add the node in param to the linked list
}

void create_node(char *line, t_struct *u)
{
	//save data in the struct and add it to node list
	t_node 	*new;
	int i;

	i = 0;
	///check the format %sname %d %d is correct
	while (ft_isspace(line))
		line++;
	while (ft_isdigit(line) || ft_isalpha(line))
		i++;
	u->list->node.name = ft_strndup(line);
	line += i;
	while (ft_isspace(line))
		line++;
	u->list->node.x = ft_atoi(line);
	while (ft_isdigit(line))
		line++;
	u->list->node.y = ft_atoi(line);
	u->list->node.cnt = ++u.index;
	u->list->node.nb_connections = -1;
	u->list->connected_to = (char**)malloc(sizeof(char*) * u->list->connected_to);
	u->list->info = u.index;
	add_node(&u->list, new);

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
	if (!line || (line[0] != ft_isdigit(line) || ft_isalpha(line)))
		return (0);
	while (ft_isdigit(line) || ft_isalpha(line))
		i++;
	u->node->name = ft_strndup(line);
	line += i;
	while (ft_isspace(line))
		line++;
	if (!line || line[0] != ft_isdigit(line))
			return (0);
	u->node->x = ft_atoi(line);
	while (ft_isdigit(line))
		line++;
	if (line && line[0] != ft_isdigit(line))
			return (0);
	u->node->y = ft_atoi(line);
	return (1);
}


//has to create an elem + add to the list
int start_or_end(char *line, t_struct *u)
{
	if (u->start == 1 && u->end == 1)
	{
		ft_putstr("too many edges, error!\n");
		return (0);
	}
	else if (ft_strcmp(line + 2, "start") && u->start = 0 && ++u->start)
	{
		printf("parse start\n");
		create_node(u, node);
	}

	else if (ft_strcmp(line + 2, "end") && u->end = 0 && ++u->end)
	{
		printf("parse end\n");
		create_node(u, node);
	}
	else
	{
		ft_putstr("START END FORMAT ERROR\n");
		return (0);
	}
	return (1);
}

int parse(char *argv, t_struct *u)
{
	int i;
	char *line;

	//index of elem;
	u->index = -1;
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
			if (line[1] == '#') // == double ##, start, end ??
				if (!(start_or_end(line, u))
					return (0);
			else //== normal comment
				free(line);
		else //if != #
		{
			if (check_node(line, u)) //if new node
			{
				create_node(u);
			}
			else if (node_connection(line, u)) //or connection ??
			{
					create_hash_table(u);
					add_connection(line, u);
					free(line);
			}
			else //different ?? (error ?)
				break ;
		}
	}

	//BULLSHIT ?
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
