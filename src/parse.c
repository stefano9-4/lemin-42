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


// t_node		*new_object(void *inf, int id)
// {
// 	t_obj *new;

// 	if (!(new = (t_obj *)malloc(sizeof(*new))))
// 		return (NULL);
// 	new->obj = inf;
// 	new->id = id;
// 	new->next = NULL;
// 	return (new);
// }

void		add_node(t_lemlist **list, t_lemlist *new)
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
	return (1);
	//create hash table of connections
}

int check_connection(char *line, t_struct *u)
{
	//check the format N-N
	//go through the name list and check if valid ????????
	//format name-name
	int i;
	int x;
	int ptr;
	t_lemlist *next;
	t_lemlist *next2;

	i = 0;
	while (ft_isdigit(line[i]) || ft_isalpha(line[i]))
		i++;
	x = 0;
	u->t_name1 = ft_strndup(line, i);
	while (u->lemlist->next)
	{
			if (ft_strncmp(line, u->lemlist->node.name, i) == 0)
				break ;
			next = u->lemlist->next;

	}
	line += i;
	if (*line != '-')
		return (0);
	line++;
	i++;
	ptr = i;
	while (ft_isdigit(line[i]) || ft_isalpha(line[i]))
		i++;
	u->t_name2 = ft_strndup(line, i);
	while (u->lemlist->next)
	{
			if (ft_strncmp(line, u->lemlist->node.name, i) == 0)
				return (1);
			next2 = u->lemlist->next;
	}
	return (0);
}

void add_connection(char *line, t_struct *u /*+ node*/)
{
	t_lemlist *next;

	while (u->lemlist->next)
	{
		if (ft_strcmp(u->t_name1, u->lemlist->node.name) == 0)
		{
				u->lemlist->node.nb_connections++;
				u->lemlist->node.connected_to[u->lemlist->node.nb_connections] = ft_strdup(u->t_name2);
		}
		if (ft_strcmp(u->t_name2, u->lemlist->node.name) == 0)
		{
				u->lemlist->node.nb_connections++;
				u->lemlist->node.connected_to[u->lemlist->node.nb_connections] = ft_strdup(u->t_name1);
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
	t_lemlist 	*new;
	int i;

	i = 0;
	///check the format %sname %d %d is correct
	while (*line == ' ' || *line == '\t')
		line++;
	while (ft_isdigit(*line) || ft_isalpha(*line))
		i++;
	u->lemlist->node.name = strndup(line, i);
	line += i;
	while (*line == ' ' || *line == '\t')
		line++;
	u->lemlist->node.x = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	u->lemlist->node.y = ft_atoi(line);
	u->lemlist->node.cnt = ++u->index;
	u->lemlist->node.nb_connections = -1;
	u->lemlist->node.connected_to = (char**)malloc(sizeof(char*));
	u->lemlist->info = u->index;
	add_node(&u->lemlist, new);
}

//should do additional checks for validity ?????

int check_node(char *line, t_struct *u)
{
	int i;
	int cnt;
	char *tab;

	cnt = 0;
	i = 0;
	///check the format %sname %d %d is correct
	while ((*line == ' ' || *line == '\t') && i++)
	{
		line++;
		i++;
	}	
	cnt = i;
	if (!ft_isdigit(*line) && !ft_isalpha(*line))
	{
		printf("DJSDSHJDS\n");
		return (0);
	}
	while ((ft_isdigit(line[i]) || ft_isalpha(line[i])))
		i++;
	printf("%d\n", i - cnt);
	u->lemlist->node.name = ft_strndup(line, i - cnt);
	line += i;
	printf("char = %c\n", *line);
	printf("CHECK_NODE\n");
	printf("line = %s\n", line);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (!*line || !ft_isdigit(*line))
			return (0);
	u->lemlist->node.x = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (!ft_isdigit(*line))
			return (0);
	u->lemlist->node.y = ft_atoi(line);
	return (1);
}


//has to create an elem + add to the list
int start_or_end(char *line, t_struct *u)
{
	printf("LINE == %s\n", line);
	if (u->start == 1 && u->end == 1)
	{
		ft_putstr("too many edges, error!\n");
		return (0);
	}
	else if ((ft_strcmp(line + 2, "start") == 0) && u->start == 0)
	{
		free(line);
		get_next_line(u->fd, &line);
		printf("%d\n", u->ants);
		printf("parse start\n");
		check_node(line, u);
		create_node(line, u);
		++u->start;
	}

	else if ((ft_strcmp(line + 2, "end") == 0) && u->end == 0 )
	{
		free(line);
		get_next_line(u->fd, &line);
		printf("parse end\n");
		check_node(line, u);
		create_node(line, u);
		++u->end;
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
	u->start = 0;
	u->end = 0;
	get_next_line(u->fd, &line);
	while (!ft_isdigit(line[0]))
	{
		free(line);
		get_next_line(u->fd, &line);
	}
	u->ants = ft_atoi(line);
	free(line);
	while (get_next_line(u->fd, &line))
	{
		if (line && line[0] == '#')
		{
			if (line[1] == '#') // == double ##, start, end ??
			{
				if (!(start_or_end(line, u)))
					return (0);
			
			}
			else //== normal comment
			{
				printf("comment found\n");
				free(line);
			}
		}
		
		else //if != #
		{
		printf("here\n");
			if (check_node(line, u)) //if new node
			{
				create_node(line, u);
			}
			else if (check_connection(line, u)) //or connection ??
			{
					//create_hash_table(u);
					add_connection(line, u);
					free(line);
			}
			else //different ?? (error ?)
				break ;
		}
	}

	//BULLSHIT ?
	// while (get_next_line(u->fd, &line))
	// {
	// 	if (line[0] == '#')
	// 		free(line);
	// 	else
	// 	{
	// 		if (connection_format(u))
	// 			add_to_hash(u);
	// 		free(line);
	// 	}
	// }
	return (1);
}
