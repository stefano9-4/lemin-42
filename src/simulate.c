/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:49:46 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/25 15:04:10 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	send_waves2(t_struct *u)
{
	while (u->paths[u->path_i][u->j] != u->src)
	{
		if (u->ants_arrived == u->ants)
			break ;
		if (u->paths[u->path_i][u->j] == u->snk
				&& u->hm->list[u->paths[u->path_i][u->j - 1]]->has_ant == 1)
		{
			u->hm->list[u->paths[u->path_i][u->j]]->ant_ID = u->hm->list
				[u->paths[u->path_i][u->j - 1]]->ant_ID;
			++u->ants_arrived;
		}
		if (u->paths[u->path_i][u->j - 1] == u->src
				&& u->ants_sent != u->ants + 1)
		{
			u->hm->list[u->paths[u->path_i][u->j]]->ant_ID = u->ants_sent;
			u->hm->list[u->paths[u->path_i][u->j]]->has_ant = 1;
		}
		if (u->hm->list[u->paths[u->path_i][u->j - 1]]->has_ant == 1)
		{
			u->hm->list[u->paths[u->path_i][u->j]]->ant_ID = u->hm->list
				[u->paths[u->path_i][u->j - 1]]->ant_ID;
			u->hm->list[u->paths[u->path_i][u->j]]->has_ant = 1;
		}
		--u->j;
	}
}

int		send_waves(t_struct *u, int i, int len[u->num_paths], int print)
{
	u->ants_arrived = 0;
	u->ants_sent = 0;
	u->flag = 0;
	u->sol_len = 0;
	while (u->ants_arrived < u->ants)
	{
		u->path_i = -1;
		while (++u->path_i <= i)
		{
			if (u->ants_sent < u->ants && !u->flag)
				++u->ants_sent;
			else
			{
				++u->flag;
				u->ants_sent = 0;
				u->hm->list[u->src]->has_ant = 0;
			}
			len_path(u);
			send_waves2(u);
		}
		u->sol_len++;
		if (u->ants_arrived != u->ants && print)
			print_sol(u, i, len);
	}
	return (u->sol_len - 1);
}

int		set_paths(t_struct *u, int len[u->num_paths])
{
	u->i = -1;
	while (++u->i < u->num_paths)
	{
		u->j = -1;
		while (u->paths[u->i][++u->j] != u->snk)
		{
			u->hm->list[u->paths[u->i][u->j]]->ant_ID = 0;
			u->hm->list[u->paths[u->i][u->j]]->has_ant = 0;
		}
		u->hm->list[u->snk]->ant_ID = 0;
		u->hm->list[u->snk]->has_ant = 0;
		len[u->i] = u->j;
	}
}

int		find_best_sol(t_struct *u, int sol[u->num_paths])
{
	u->i = -1;
	u->min = INT_MAX;
	while (++u->i < u->num_paths)
	{
		if (sol[u->i] < u->min)
		{
			u->min = sol[u->i];
			u->min_i = u->i;
		}
	}
}

int		simulate(t_struct *u)
{
	int		len[u->num_paths];
	int		sol[u->num_paths];
	int		tmp;

	sort_paths(u);
	set_paths(u, len);
	u->i = -1;
	while (++u->i < u->num_paths)
	{
		sol[u->i] = send_waves(u, u->i, len, 0);
		tmp = -1;
		while (++tmp < u->num_paths)
		{
			u->j = -1;
			while (++u->j <= len[tmp])
			{
				u->hm->list[u->paths[tmp][u->j]]->ant_ID = 0;
				u->hm->list[u->paths[tmp][u->j]]->has_ant = 0;
			}
		}
	}
	find_best_sol(u, sol);
	printf("sol: %d (%d)\n", u->min_i, sol[u->min_i]);
	send_waves(u, u->min_i, len, 1);
}
