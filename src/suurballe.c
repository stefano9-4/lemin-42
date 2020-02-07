/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:18:07 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/07 16:12:31 by spozzi           ###   ########.fr       */
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

void	bellmanFord2(t_struct *u, int *bf_path)
{
	long	dist[u->num_nodes];
	int		i;
	int		j;
	int		i_rel;
	int		is_updt;
	long	weight;
	long	weight2;
	int		is_i_path;
	int		is_j_path;
	int		w;

	i = -1;
	while (++i < u->num_nodes)
		dist[i] = INT_MAX;
	dist[u->src] = 0;
	i_rel = -1;
	// Relax edges |V - 1| times
	// printf("+++++++++++++++++++++++++++++++++++++++\n");
	while (++i_rel < u->num_nodes - 1)
	{
		i = -1;
		is_updt = 0;
		// if (u->curr_path >= 11)
			// printf("aaaaaa %d\n", i_rel);
		while (++i < u->num_edges && u->edge_list[i][0] != -1
				&& u->edge_list[i][1] != -1)
		{
			w = 2;
			weight = u->graph[get_offset_2d(u, u->edge_list[i][0], u->edge_list[i][1])];
			weight2 = u->graph[get_offset_2d(u, u->edge_list[i][1], u->edge_list[i][0])];
			is_i_path = is_in_BF_path(u, u->edge_list[i][0], bf_path);
			is_j_path = is_in_BF_path(u, u->edge_list[i][1], bf_path);
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
				if (dist[u->edge_list[i][0]] + weight < dist[u->edge_list[i][1]] && ++is_updt)
				{
					// if (dist[u->edge_list[i][0]] + weight > INT_MAX)
					// 	dist[u->edge_list[i][1]] = weight;
					// else
						dist[u->edge_list[i][1]] = dist[u->edge_list[i][0]] + weight;
					u->hm->list[u->edge_list[i][1]]->prev = u->edge_list[i][0];
					// if (u->curr_path == 11)
					// 	printf("1:(%s,%s): %ldlong\n", u->hm->list[u->edge_list[i][0]]->name,u->hm->list[u->edge_list[i][1]]->name, dist[u->edge_list[i][1]]);
				}
			if (weight2 != 0 || weight2 == w)
				if (dist[u->edge_list[i][1]] + weight2 < dist[u->edge_list[i][0]] && ++is_updt)
				{
					// if (dist[u->edge_list[i][1]] + weight2 > INT_MAX)
					// 	dist[u->edge_list[i][0]] = weight2;
					// else
						dist[u->edge_list[i][0]] = dist[u->edge_list[i][1]] + weight2;
					u->hm->list[u->edge_list[i][0]]->prev = u->edge_list[i][1];
					// if (u->curr_path == 11)
					// 	printf("2:(%s,%s) %ldlong\n", u->hm->list[u->edge_list[i][1]]->name, u->hm->list[u->edge_list[i][0]]->name, dist[u->edge_list[i][0]]);
				}
		}
		if (is_updt == 0)
			break ;
		// if (u->curr_path >= 11)
			// printf("bbbbb\n");
		// If no change is made just stop
	}
	// if (u->curr_path >= 11)
		// printf("ccccccc\n");
}

int		*inverse_BF_path(t_struct *u)
{
	int	i;
	int	l_path;
	int	*bf_path;

	// printf("curr: %d\n", u->curr_path -1);
	bf_path = u->paths[u->curr_path - 1];
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

void	suurballe(t_struct *u)
{
	int	*bf_path;
	int i_suur;

	i_suur = -1;
	// create most paths as possible
	while (++i_suur < u->max_paths)
	{
		bf_path = inverse_BF_path(u);
		int i = -1;
		while (++i < u->num_nodes)
			u->hm->list[i]->prev = -1;
		bellmanFord2(u, bf_path);
		// check if other paths can be created
		if (!is_snk_src_connected(u))
			break ;
		u->paths[u->curr_path++] = get_BF_path(u);
		printf("fml\n");
		if (!u->paths[u->curr_path - 1] && --u->curr_path)
			break ;
		// int j = -1;
		// printf("i_cuur_path: %d\n", u->curr_path - 1);
		// while (++j + 1)
		// {
		// 	printf("%d(%s) ", u->paths[u->curr_path - 1][j], u->hm->list[u->paths[u->curr_path - 1][j]]->name);
		// 	if (u->paths[u->curr_path - 1][j] == u->snk)
		// 		break ;
		// }
		// printf("\n");
	}
	// print all paths
	// }
}
