/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:17:51 by lutomasz          #+#    #+#             */
/*   Updated: 2020/01/28 15:17:54 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		get_offset_3d(t_struct u, int x, int y, int z)
{
	return (z * u.num_nodes * u.num_nodes) + (y * u.num_nodes) + x;
}

int		get_offset_2d(t_struct *u, int x, int y)
{
	return (y * u->num_nodes) + x;
}

void	print_graph(t_struct *u)
{
	int i = -1;
	int j;
	
	printf("ID: %s\n", u->id);
	while (++i < (u->num_nodes))
	{
		j = -1;
		while (++j < u->num_nodes)
			printf("%d ", u->graph[get_offset_2d(u, i, j)]);
		printf("\n");
	}
}

void	set_zeros(t_struct *u, int size)
{
	int i;

	i = -1;
	while (++i < size)
		u->graph[i] = 0;
}

int		has_space(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == ' ')
			return (1);
	return (0);
}

void	print_stuff(t_struct *u)
{
	int aa;
	int i;
	int j;
	int print_hMap = 1;
	int print_graph = 1;

	if (print_hMap)
	{
		aa = -1;
		printf("HashMap values:\n");
		while (++aa < u->num_nodes)
		{
			int pos = hashCode(u->hm, aa);
			printf("key:		%d\n", u->hm->list[pos]->key);
			printf("name:		%s\n", u->hm->list[pos]->name);
			printf("prev:		%d\n", u->hm->list[pos]->prev);
			printf("has_ant:	%d\n", u->hm->list[pos]->has_ant);
			printf("isVisited:	%d", u->hm->list[pos]->isVisited);
			if (aa != u->num_nodes - 1)
				printf("\n\n");
			// printf("%s ", hm_lookup(u->hm, aa));
		}
		printf("\n\n-------------------\n\n");
	}
	if (print_graph)
	{
		i = -1;
		printf("Graph:\n");
		while (++i < (u->num_nodes))
		{
			j = -1;
			while (++j < u->num_nodes)
				printf("%d ", u->graph[get_offset_2d(u, i, j)]);
			printf("\n");
		}
		printf("Source (k, n):	(%d, %s)\n", u->src, u->hm->list[hashCode(u->hm, u->src)]->name);
		printf("Sink   (k, n):	(%d, %s)\n", u->snk, u->hm->list[hashCode(u->hm, u->snk)]->name);
		printf("\n-------------------\n");
	}
}
