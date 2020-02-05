/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:18:07 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/02 15:38:03 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_in_BF_path(t_struct *u, int v, int *bf_path)
{
	int		i;

	i = -1;
	while (bf_path[++i] != u->snk)
		if (bf_path[i] == v)
			return (1);
	return (0);
}

void bellmanFord2(t_struct *u, int *bf_path)
{
	int		dist[u->num_nodes];
	int		i;
	int		j;
	int		i_rel;
	int		is_updt;
	int		weight;
	int		is_i_path;
	int		is_j_path;
	int		w;


	i = -1;
	while (++i < u->num_nodes)
		dist[i] = INT_MAX;
	dist[u->src] = 0;
	i_rel = -1;
	// Relax edges |V - 1| times
	while (++i_rel < u->num_nodes - 1)
	{
		i = -1;
		is_updt = 0;
		while (++i < u->num_nodes) // u
		{
			j = -1;
			while (++j < u->num_nodes) // v
			{
				w = 2;
				weight = u->graph[get_offset_2d(u, i, j)];
				is_i_path = is_in_BF_path(u, i, bf_path);
				is_j_path = is_in_BF_path(u, j, bf_path);
				if (is_i_path && !is_j_path)
				{
					// weight 1 || ####(0 and same)####   <-------------------
					w = 1;
				}
				else if (!is_i_path && is_j_path)
				{
					// weight 1
					w = 1;
				}
				else if (is_i_path && is_j_path)
				{
					// weight -1
					w = -1;
				}
				// i && j not in path BF
				if (weight != 0 || weight == w)
				{
					if ((double)dist[i] + (double)weight < (double)dist[j] && ++is_updt)
					{
						// if (dist[i] == INT_MAX)
						// 	dist[j] = weight;
						// else
							dist[j] = dist[i] + weight;
						u->hm->list[j]->prev = i;
					}
				}
			}
		}
		// If no change is made just stop
		if (is_updt == 0)
			break ;
	}
}

int		*inverse_BF_path(t_struct *u)
{
	int	i;
	int	l_path;
	int	*bf_path;

	bf_path = get_BF_path(u);
	l_path = 0;
	while (bf_path[l_path] != u->snk)
		++l_path;
	while (l_path - 1 >= 0)
	{
		u->graph[get_offset_2d(u, bf_path[l_path], bf_path[l_path - 1])] = -1;
		u->graph[get_offset_2d(u, bf_path[l_path - 1], bf_path[l_path])] = 0;
		--l_path;
	}
	return (bf_path);
}

void	remove_src_out(t_struct *u)
{
	int i;

	i = -1;
	while (++i < u->num_nodes)
	{
		u->graph[get_offset_2d(u, u->snk, i)] = 0;
		//u->graph[get_offset_2d(u, i, u->snk)] = 0;
	}
}

void	suurballe(t_struct *u)
{
	int	*bf_path;
	int i_suur;

	i_suur = -1;
	//remove_src_out(u);
	// create most paths as possible
	while (++i_suur < u->max_paths)
	{
		bf_path = inverse_BF_path(u);
		bellmanFord2(u, bf_path);
		//print_graph(u);
		// check if other paths can be created
		if (!is_snk_src_connected(u))
			break ;
		u->paths[u->curr_path++] = get_BF_path(u);
		int j = -1;
		while (++j + 1)
			if (u->paths[u->curr_path-1][j] == u->snk)
				break ;
	}
	// print all paths
	int i = -1;
	while (++i < u->curr_path)
	{
		printf("path num %d:\n", i);
		int j = -1;
		while (++j + 1)
		{
			printf("%d(%s) ", u->paths[i][j], u->hm->list[u->paths[i][j]]->name);
			if (u->paths[i][j] == u->snk)
				break ;
		}
		printf("\n");
	}
}
