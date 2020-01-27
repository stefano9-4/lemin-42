/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:00:33 by spozzi            #+#    #+#             */
/*   Updated: 2020/01/27 16:09:02 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_q_empty(t_struct *u, int q[u->num_nodes])
{
	int		i;

	i = -1;
	while (++i < u->num_nodes)
		if (q[i] != -1)
			return (0);
	return (1);
}

int		deQ(t_struct *u, int q[u->num_nodes])
{
	int i;

	i = -1;
	while (++i < u->num_nodes)
		if (q[i] != -1)
			return (i);
	return (-1);
}

void	bfs(t_struct *u)
{
	int		q[u->num_nodes];
	//int		pred[u->num_nodes];
	int		i;
	int		i_enq;
	int		i_deq;
	int 	current;

	i_enq = 0;
	i_deq = 0;
	i = -1;
	while (++i < u->num_nodes)
		q[i] = -1;
	q[i_enq++] = u->src;
	u->hm->list[u->src]->isVisited = 1;
	while (!is_q_empty(u, q))
	{
		current = q[i_deq];
		q[i_deq++] = -1;
		i = -1;
		while (++i < u->num_nodes)
		{
			if (u->graph[get_offset_2d(u, current, i)] == 1)
			{
				if (!u->hm->list[i]->isVisited)
				{
					u->hm->list[i]->isVisited = 1;
					u->hm->list[i]->prev = current;
					q[i_enq++] = i;
				}
			}
		}
	}
}
