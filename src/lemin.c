/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:46:38 by spozzi            #+#    #+#             */
/*   Updated: 2020/01/15 13:12:31 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// int		offset(t_struct u, int x, int y, int z)
// {
// 	return (z * u.nodes * u.nodes) + (y * u.nodes) + x;
// }

// int		is_q_empty(int *q)
// {
// 	int		i;

// 	i = -1;
// 	while (q[++i])
// 		if (q[i] != 0)
// 			return (0);
// 	return (1);
// }

// int		find_min_dist(int *q, int *dist)
// {
// 	int		i;
// 	int		min;
// 	int		min_i;

// 	// find first V in Q
// 	i = -1;
// 	while (q[++i])
// 		if (q[i] != 0)
// 			break ;
// 	// store dist(V) in min
// 	min = dist[i];
// 	// find index of overall min dist(V) in Q
// 	i = 0;
// 	while (q[++i])
// 	{
// 		// check only if V is in Q
// 		if (q[i] != 0 && dist[i] < min)
// 		{
// 			min = dist[i];
// 			min_i = i;
// 		}
// 	}
// 	return (min_i);
// }

// int		dijkstra(t_struct *u)
// {
// 	u->dist = (int*)malloc(sizeof(int) * u->nodes);
// 	u->prev = (int*)malloc(sizeof(int) * u->nodes);
// 	u->q = (int*)malloc(sizeof(int) * u->nodes);
// 	u->i = -1;
// 	while (++u->i < u->nodes)
// 	{
// 		u->dist[u->i] = INT_MAX;
// 		u->prev[u->i] = -1;
// 		u->q[u->i] = 1;
// 	}
// 	u->dist[u->src] = 0;
// 	while (!is_q_empty(u->q))
// 	{
// 		u->v = find_min_dist(u->q, u->dist);
// 		u->q[u->v] = 0;
// 		if (u->v == u->snk)
// 			break ;
// 		// find all neighbors (in Q) of V
// 	}
// }

int		main(int ac, char **av)
{
	t_struct	u;

	//u = (t_struct*)malloc(sizeof(t_struct));
	u.nodes = 5;

	if (ac == 2 && ((u.fd = open(av[1], O_RDONLY)) != 0))
		if (!(parse(av[1], &u)))
			printf("ERROR\n");
	u.graph = (int*)malloc(sizeof(int) * u.nodes * u.nodes * 2);
}
