/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 12:18:07 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/27 14:30:53 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_in_bf_path(t_struct *u, int v, int *bf_path)
{
	int		i;

	i = -1;
	while (bf_path[++i] != u->snk)
		if (bf_path[i] == v)
			return (1);
	return (0);
}

void	bellman_ford2_bis(t_struct *u, int *bf_path, long dist[u->num_nodes])
{
	u->is_i_path = is_in_bf_path(u, u->edge_lst[u->i][0], bf_path);
	u->is_j_path = is_in_bf_path(u, u->edge_lst[u->i][1], bf_path);
	if (u->is_i_path && !u->is_j_path)
		u->w = 1;
	else if (!u->is_i_path && u->is_j_path)
		u->w = 1;
	else if (u->is_i_path && u->is_j_path)
		u->w = -1;
	if (u->w8_l != 0 || u->w8_l == u->w)
		if (dist[u->edge_lst[u->i][0]] + u->w8_l < dist[u->edge_lst[u->i][1]]
			&& ++u->is_updt)
		{
			dist[u->edge_lst[u->i][1]] = dist[u->edge_lst[u->i][0]] + u->w8_l;
			u->hm->list[u->edge_lst[u->i][1]]->prev = u->edge_lst[u->i][0];
		}
	if (u->w82_l != 0 || u->w82_l == u->w)
		if (dist[u->edge_lst[u->i][1]] + u->w82_l < dist[u->edge_lst[u->i][0]]
			&& ++u->is_updt)
		{
			dist[u->edge_lst[u->i][0]] = dist[u->edge_lst[u->i][1]]
				+ u->w82_l;
			u->hm->list[u->edge_lst[u->i][0]]->prev = u->edge_lst[u->i][1];
		}
}

void	bellman_ford2(t_struct *u, int *bf_path)
{
	long	dist[u->num_nodes];

	u->i = -1;
	while (++u->i < u->num_nodes)
		dist[u->i] = INT_MAX;
	dist[u->src] = 0;
	u->i_rel = -1;
	while (++u->i_rel < u->num_nodes - 1)
	{
		u->i = -1;
		u->is_updt = 0;
		while (++u->i < u->num_edges && u->edge_lst[u->i][0] != -1
				&& u->edge_lst[u->i][1] != -1)
		{
			u->w = 2;
			u->w8_l = u->graph[get_offset_2d(u, u->edge_lst[u->i][0],
				u->edge_lst[u->i][1])];
			u->w82_l = u->graph[get_offset_2d(u, u->edge_lst[u->i][1],
				u->edge_lst[u->i][0])];
			bellman_ford2_bis(u, bf_path, dist);
		}
		if (u->is_updt == 0 || u->i_rel > 300)
			break ;
	}
}

int		*inverse_bf_path(t_struct *u)
{
	int	i;
	int	l_path;
	int	*bf_path;

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
	int i;

	i_suur = -1;
	while (++i_suur < u->max_paths)
	{
		printf("iter: %d\n", i_suur);
		bf_path = inverse_bf_path(u);
		i = -1;
		while (++i < u->num_nodes)
			u->hm->list[i]->prev = -1;
		bellman_ford2(u, bf_path);
		// if (!is_snk_src_connected(u))
		// 	return (0);
		u->paths[u->curr_path++] = get_bf_path(u);
		if (!u->paths[u->curr_path - 1] && --u->curr_path)
			break ;
	}
	u->num_paths = i_suur + 1;
	// return (1);
}
