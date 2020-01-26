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

void		add_node(t_node **list, t_node *new)
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
	printf("OBJ ADDED\n");
}

void		add_cons(t_cons **list, t_cons *new)
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
	printf("CON ADDED\n");
}
/*
**	get start node and end node infos !!!to do
*/

int create_hash_table(t_struct *u)
{
	return (1);
	//create hash table of connections
}


//fails to send the rightt value
int check_connection(char *line, t_struct *u)
{
	//check the format N-N
	//go through the name list and check if valid ????????
	//format name-name
	int i;
	int x;
	int ptr;
	t_node *next;
	t_node *next2;


	next = (t_node*)malloc(sizeof(next));
	next2 = (t_node*)malloc(sizeof(next2));
	i = 0;
	while (ft_isdigit(line[i]) || ft_isalpha(line[i]))
		i++;
	x = 0;
	u->t_name1 = ft_strndup(line, i);
	while (u->node != NULL)
	{
		next = u->node->next;
			if (ft_strncmp(line, u->node->name, i) == 0)
				break ;
		u->node = next;

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
	//doesnt send the right value >>>>>
	u->node = u->first;
	while (u->node != NULL)
	{
		printf("DHSDHJFDJFJDFJDHFJKKJKSHDSDHJSJKDS\n");
		next2 = u->node->next;
			if (ft_strncmp(line, u->node->name, i) == 0)
				return (1);
		u->node = next2;
	}
	return (1);
}

void add_connection(char *line, t_struct *u /*+ node*/)
{
	t_cons *next;
	t_cons *next2;
	t_node	*plus;

	plus = (t_node*)malloc(sizeof(plus));
	next = (t_cons*)malloc(sizeof(next));
	next2 = (t_cons*)malloc(sizeof(next2));
	u->node = u->first;
	while (u->node != NULL)
	{
		plus = u->node->next;
		printf("NAME %s\n", u->t_name1);
		printf("NAME %s\n", u->t_name2);
		printf("NAME2 %s\n", u->node->name);
		printf("NAME2 %s\n", u->node->name);
		if (ft_strcmp(u->t_name1, u->node->name) == 0)
		{
				printf("hey1111\n");
				u->node->nb_connections++;
				//u->node->connected_to[u->node->nb_connections] = ft_strdup(u->t_name2);
				add_cons(&u->node->links, next);
		}
		if (ft_strcmp(u->t_name2, u->node->name) == 0)
		{
				printf("hey222222\n");
				u->node->nb_connections++;
			//	u->node->connected_to[u->node->nb_connections] = ft_strdup(u->t_name1);
				add_cons(&u->node->links, next);
		}
		u->node = plus;
	}
	// free(u->t_name1);
	// free(u->t_name2);
	//add the node in param to the linked list
}


//problem with name
void create_node(char *line, t_struct *u)
{
	//save data in the struct and add it to node list
	t_node 	*new;
	int i;

	new = (t_node *)malloc(sizeof(new));
	i = 0;
	///check the format %sname %d %d is correct
	while (*line == ' ' || *line == '\t')
		line++;
	while (ft_isdigit(line[i]) || ft_isalpha(line[i]))
	{
		i++;
	}
	
	printf("\n\n");
	printf("i:	%d\n", i);
	char *str;
	// new->name = (char*)malloc(sizeof(char) * i + 1);
	// new->name[i] = '\0';
	// while (--i >= 0)
	// 	new->name[i] = line[i];
	str = (char*)malloc(sizeof(char) * i + 1);
	str[i] = '\0';
	while (--i >= 0)
		str[i] = line[i];
	printf("RIGHT NAME ISSSSS %s\n", line);
	//new->name = ft_strndup(test, i);
	printf("TTEST: %s\n", str);


	line += i;
	while (*line == ' ' || *line == '\t')
		line++;
	new->x = ft_atoi(line);
	//printf("got @@@@@@@@@@@@@@@@@@@@@@@@ %s|\n", new->name);
	while (ft_isdigit(*line))
		line++;
	new->y = ft_atoi(line);
	new->cnt = ++u->index;
	new->nb_connections = -1;
	new->connected_to = (char**)malloc(sizeof(char*));
	//u->info = u->index;
	new->next = NULL;
	new->links = NULL;
	// printf("char = %c\n", *line);
	// printf("CHECK_NODE\n");
	// printf("line = %s\n", line);
	add_node(&u->node, new);
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
	line += i;
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (!*line || !ft_isdigit(*line))
			return (0);
	while (*line && ft_isdigit(*line))
		line++;
	if (!(line[1] >= '0' && line [1] <= '9'))
	{
		printf("BLOCK CHECK_NODE\n");
		return (0);
	}	
	return (1);
}


//has to create an elem + add to the list
int start_or_end(char *line, t_struct *u)
{
	//printf("LINE == %s\n", line);
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
		//check_node(line, u);
		create_node(line, u);
		++u->start;
		u->first = u->node;
	}

	else if ((ft_strcmp(line + 2, "end") == 0) && u->end == 0 )
	{
		free(line);
		get_next_line(u->fd, &line);
		printf("parse end\n");
		//check_node(line, u);
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
	i = 0;
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
		printf("TOUR === %d\n", i);
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
			printf("%s\n", line);
			if (check_node(line, u) == 1) //if new node
			{
			//	break ;
				printf("CREATING NODE\n" );
				create_node(line, u);
			}
			else if (check_connection(line, u)) //or connection ??
			{
					printf("CREATING connection\n");
					//create_hash_table(u);
					add_connection(line, u);
					//free(line);
			}
			else //different ?? (error ?)
			{
				printf("NOTHING\n");
				break ;
			}
			//free(line);
			printf("INFINITE LOOP\n");
		}
		i++;
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
