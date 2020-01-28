/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:04:48 by spozzi            #+#    #+#             */
/*   Updated: 2020/01/27 13:48:19 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_table	*createHashMap(int size)
{
	t_table	*t;
	int		i;

	t = (t_table*)malloc(sizeof(t));
	t->size = size;
	t->list = (t_node**)malloc(sizeof(t_node*) * size);
	if (!t || !t->list)
		return (NULL);
	i = -1;
	while (++i < size)
		t->list[i] = NULL;
	return (t);
}

int		hashCode(t_table *t, int key)
{
	if (key < 0)
		return - (key % t->size);
	return (key % t->size);
}

void	hm_insert(t_table *t, int key, char *name)
{
	int		pos;
	t_node	*list;
	t_node	*newNode;
	t_node	*tmp;

	pos = hashCode(t, key);
	list = t->list[pos];
	if (!(newNode = (t_node*)malloc(sizeof(t_node))))
		return ;
	tmp = list;
	while (tmp)
	{
		if (tmp->key == key)
		{
			tmp->name = name;
			return ;
		}
		tmp = tmp->next;
	}
	newNode->key = key;
	newNode->name = name;
	newNode->next = list;
	newNode->has_ant = 0;
	newNode->prev = 0;
	newNode->isVisited = 0;
	t->list[pos] = newNode;
}

char	*hm_lookup(t_table *t, int key)
{
	t_node	*list;
	t_node	*tmp;
	int		pos;

	pos = hashCode(t, key);
	list = t->list[pos];
	tmp = list;
	while (tmp)
	{
		if (tmp->key == key)
			return (tmp->name);
		tmp = tmp->next;
	}
	return ("error");
}
