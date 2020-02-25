/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:00:33 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/25 13:34:34 by spozzi           ###   ########.fr       */
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

void	bfs(t_struct *u)
{
	int		q[u->num_nodes];
	int		i;

	u->i_enq = 0;
	u->i_deq = 0;
	i = -1;
	while (++i < u->num_nodes)
		q[i] = -1;
	q[u->i_enq++] = u->src;
	u->hm->list[u->src]->isVisited = 1;
	while (!is_q_empty(u, q))
	{
		u->current = q[u->i_deq];
		q[u->i_deq++] = -1;
		i = -1;
		while (++i < u->num_nodes)
			if (u->graph[get_offset_2d(u, u->current, i)] == 1)
				if (!u->hm->list[i]->isVisited)
				{
					u->hm->list[i]->isVisited = 1;
					u->hm->list[i]->prev = u->current;
					q[u->i_enq++] = i;
				}
	}
	printf("snk prev %d\n", u->hm->list[u->snk]->prev);
}
