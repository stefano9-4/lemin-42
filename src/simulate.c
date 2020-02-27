/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:49:46 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/27 15:07:10 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	send_waves2(t_struct *u, int ant_pos[u->i])
{
	while (u->paths[u->path_i][u->j] != u->src)
	{
		if (u->ants_arrived == u->ants)
			break ;
		if (u->paths[u->path_i][u->j] == u->snk && u->paths[u->path_i][u->j - 1] == u->src && !u->flag)
		{
			ant_pos[u->ants_sent - 1] = u->snk;
			++u->ants_arrived;
		}
		else if (u->paths[u->path_i][u->j] == u->snk
				&& u->hm->list[u->paths[u->path_i][u->j - 1]]->has_ant == 1)
		{
			ant_pos[u->hm->list[u->paths[u->path_i][u->j - 1]]->ant_ID - 1] = u->snk;

			u->hm->list[u->paths[u->path_i][u->j]]->ant_ID = u->hm->list
				[u->paths[u->path_i][u->j - 1]]->ant_ID;
			u->hm->list[u->paths[u->path_i][u->j - 1]]->has_ant = 0;
			++u->ants_arrived;
		}
		else if (u->paths[u->path_i][u->j - 1] == u->src
				&& u->ants_sent != u->ants + 1 && !u->flag)
		{
			ant_pos[u->ants_sent - 1] = u->paths[u->path_i][u->j];

			u->hm->list[u->paths[u->path_i][u->j]]->ant_ID = u->ants_sent;
			u->hm->list[u->paths[u->path_i][u->j]]->has_ant = 1;
		}
		else if (u->hm->list[u->paths[u->path_i][u->j - 1]]->has_ant == 1)
		{
			ant_pos[u->hm->list[u->paths[u->path_i][u->j - 1]]->ant_ID - 1] = u->paths[u->path_i][u->j];

			u->hm->list[u->paths[u->path_i][u->j]]->ant_ID = u->hm->list
				[u->paths[u->path_i][u->j - 1]]->ant_ID;
			u->hm->list[u->paths[u->path_i][u->j - 1]]->has_ant = 0;
			u->hm->list[u->paths[u->path_i][u->j]]->has_ant = 1;
		}
		else
			;
		--u->j;
	}
}

int		send_waves_1(t_struct *u, int i, int len[u->num_paths], int print)
{
	u->ants_arrived = 0;
	u->ants_sent = 0;
	u->flag = 0;
	u->sol_len = 0;
	int ant_pos[u->ants];

	u->k = -1;
	while (++u->k < u->ants)
		ant_pos[u->k] = -1;

	while (u->ants_arrived < u->ants)
	{
		u->path_i = -1;
		while (++u->path_i <= i)
		{
			if (u->ants_sent < u->ants && !u->flag)
				++u->ants_sent;
			else
			{
				u->flag = 1;
				u->ants_sent = 1;
			}
			len_path(u);
			send_waves2(u, ant_pos);
		}
		u->sol_len++;
		if (u->ants_arrived <= u->ants && print)
			print_sol(u, i, len, ant_pos);
	}
	return (u->sol_len - 1);
}

int		send_waves(t_struct *u, int i, int len[u->num_paths], int print, int ants_to_send[u->num_paths])
{
	u->ants_arrived = 0;
	u->ants_sent = 0;
	u->flag = 0;
	u->sol_len = 0;
	int ant_pos[u->ants];

	u->k = -1;
	while (++u->k < u->ants)
		ant_pos[u->k] = -1;

	while (u->ants_arrived < u->ants)
	{
		u->path_i = -1;
		while (++u->path_i <= i)
		{
			if (u->ants_sent < u->ants && !u->flag)
				++u->ants_sent;
			else
			{
				u->flag = 1;
				u->ants_sent = 1;
			}
			len_path(u);
			send_waves2(u, ant_pos);
		}
		u->sol_len++;
		if (u->ants_arrived <= u->ants && print)
			print_sol(u, i, len, ant_pos);
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

int		simulate_1(t_struct *u)
{
	int		len[u->num_paths];
	int		sol[u->num_paths];
	int		tmp;

	sort_paths(u);
	set_paths(u, len);
	u->i = -1;
	while (++u->i < u->num_paths)
		sol[u->i] = 0;
	u->i = -1;
	while (++u->i < u->num_paths)
	{
		sol[u->i] = send_waves(u, u->i, len, 0);
		// printf("----sol_i: %d----\n", sol[u->i]);
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

int		simulate(t_struct *u)
{
	int		len[u->num_paths];
	int		sol[u->num_paths];
	int		tmp;

	sort_paths(u);
	set_paths(u, len);
	u->i = -1;
	while (++u->i < u->num_paths)
		sol[u->i] = 0;

	int avg_len = 0;
	int avg_steps = 0;
	int ants_to_send[u->num_paths];
	u->i = -1;
	while (++u->i < u->num_paths)
		avg_len += len[u->i];
	avg_len /= u->num_paths;

	int div_ants = u->ants / u->num_paths;
	int ant_rest = u->ants % u->num_paths;
	avg_steps = avg_len - 1 + u->ants / u->num_paths;

	u->i = -1;
	while (++u->i < u->num_paths)
		ants_to_send[u->i] = avg_steps - len[u->i] - 1;
	ants_to_send[0] += ant_rest;

	u->i = -1;
	while (++u->i < u->num_paths)
	{
		sol[u->i] = send_waves(u, u->i, len, 0, ants_to_send);
		// printf("----sol_i: %d----\n", sol[u->i]);
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
