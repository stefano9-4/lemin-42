/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:58:56 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/25 12:01:55 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	bellman_ford_bis(t_struct *u, int dist[u->num_nodes], int i)
{
	u->weight = u->graph[get_offset_2d(u, u->edge_list[i][0]
		, u->edge_list[i][1])];
	u->weight2 = u->graph[get_offset_2d(u, u->edge_list[i][1]
		, u->edge_list[i][0])];
	if (u->weight != 0)
		if ((double)dist[u->edge_list[i][0]]
			+ (double)u->weight < dist[u->edge_list[i][1]] && ++u->is_updt)
		{
			dist[u->edge_list[i][1]] = dist[u->edge_list[i][0]] + u->weight;
			u->hm->list[u->edge_list[i][1]]->prev = u->edge_list[i][0];
		}
	if (u->weight2 != 0)
		if ((double)dist[u->edge_list[i][1]] + (double)u->weight2
			< (double)dist[u->edge_list[i][0]] && ++u->is_updt)
		{
			dist[u->edge_list[i][0]] = dist[u->edge_list[i][1]] + u->weight2;
			u->hm->list[u->edge_list[i][0]]->prev = u->edge_list[i][1];
		}
}

void	bellman_ford(t_struct *u)
{
	int		dist[u->num_nodes];
	int		i;

	i = -1;
	while (++i < u->num_nodes)
		dist[i] = INT_MAX;
	dist[u->src] = 0;
	u->i_rel = -1;
	while (++u->i_rel < u->num_nodes - 1)
	{
		i = -1;
		u->is_updt = 0;
		while (++i < u->num_edges && u->edge_list[i][0] != -1
				&& u->edge_list[i][1] != -1)
			bellman_ford_bis(u, dist, i);
		if (u->is_updt == 0)
			break ;
	}
}
