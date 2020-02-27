/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:04:48 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/27 13:16:34 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_table	*create_hash_map(int size)
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

int		hash_code(t_table *t, int key)
{
	if (key < 0)
		return (-(key % t->size));
	return (key % t->size);
}

void	hm_insert(t_table *t, int key, char *name)
{
	int		pos;
	t_node	*list;
	t_node	*new_node;
	t_node	*tmp;

	pos = hash_code(t, key);
	list = t->list[pos];
	if (!(new_node = (t_node*)malloc(sizeof(t_node))))
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
	new_node->key = key;
	new_node->name = name;
	new_node->next = list;
	new_node->prev = -1;
	new_node->isVisited = 0;
	new_node->ant_ID = -1;
	t->list[pos] = new_node;
}

char	*hm_lookup(t_table *t, int key)
{
	t_node	*list;
	t_node	*tmp;
	int		pos;

	pos = hash_code(t, key);
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
