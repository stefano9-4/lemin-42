/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:49:46 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/28 15:14:40 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// void	send_waves2_1(t_struct *u, int ant_pos[u->i])
// {
// 	while (u->paths[u->path_i][u->j] != u->src)
// 	{
// 		if (u->ants_arrived == u->ants)
// 			break ;
// 		if (u->paths[u->path_i][u->j] == u->snk && u->paths[u->path_i][u->j - 1] == u->src && !u->flag)
// 		{
// 			ant_pos[u->ants_sent - 1] = u->snk;
// 			++u->ants_arrived;
// 		}
// 		else if (u->paths[u->path_i][u->j] == u->snk
// 				&& u->hm->list[u->paths[u->path_i][u->j - 1]]->has_ant == 1)
// 		{
// 			ant_pos[u->hm->list[u->paths[u->path_i][u->j - 1]]->ant_ID - 1] = u->snk;
//
// 			u->hm->list[u->paths[u->path_i][u->j]]->ant_ID = u->hm->list
// 				[u->paths[u->path_i][u->j - 1]]->ant_ID;
// 			u->hm->list[u->paths[u->path_i][u->j - 1]]->has_ant = 0;
// 			++u->ants_arrived;
// 		}
// 		else if (u->paths[u->path_i][u->j - 1] == u->src
// 				&& u->ants_sent != u->ants + 1 && !u->flag)
// 		{
// 			ant_pos[u->ants_sent - 1] = u->paths[u->path_i][u->j];
//
// 			u->hm->list[u->paths[u->path_i][u->j]]->ant_ID = u->ants_sent;
// 			u->hm->list[u->paths[u->path_i][u->j]]->has_ant = 1;
// 		}
// 		else if (u->hm->list[u->paths[u->path_i][u->j - 1]]->has_ant == 1)
// 		{
// 			ant_pos[u->hm->list[u->paths[u->path_i][u->j - 1]]->ant_ID - 1] = u->paths[u->path_i][u->j];
//
// 			u->hm->list[u->paths[u->path_i][u->j]]->ant_ID = u->hm->list
// 				[u->paths[u->path_i][u->j - 1]]->ant_ID;
// 			u->hm->list[u->paths[u->path_i][u->j - 1]]->has_ant = 0;
// 			u->hm->list[u->paths[u->path_i][u->j]]->has_ant = 1;
// 		}
// 		else
// 			;
// 		--u->j;
// 	}
// }

// int		send_waves_1(t_struct *u, int i, int len[u->num_paths], int print)
// {
// 	u->ants_arrived = 0;
// 	u->ants_sent = 0;
// 	u->flag = 0;
// 	u->sol_len = 0;
// 	int ant_pos[u->ants];
//
// 	u->k = -1;
// 	while (++u->k < u->ants)
// 		ant_pos[u->k] = -1;
//
// 	while (u->ants_arrived < u->ants)
// 	{
// 		u->path_i = -1;
// 		while (++u->path_i <= i)
// 		{
// 			if (u->ants_sent < u->ants && !u->flag)
// 				++u->ants_sent;
// 			else
// 			{
// 				u->flag = 1;
// 				u->ants_sent = 1;
// 			}
// 			len_path(u);
// 			send_waves2(u, ant_pos);
// 		}
// 		u->sol_len++;
// 		if (u->ants_arrived <= u->ants && print)
// 			print_sol(u, i, len, ant_pos);
// 	}
// 	return (u->sol_len - 1);
// }

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

// int		find_best_sol(t_struct *u, int sol[u->num_paths])
// {
// 	u->i = -1;
// 	u->min = INT_MAX;
// 	while (++u->i < u->num_paths)
// 	{
// 		if (sol[u->i] < u->min)
// 		{
// 			u->min = sol[u->i];
// 			u->min_i = u->i;
// 		}
// 	}
// }

// int		simulate_1(t_struct *u)
// {
// 	int		len[u->num_paths];
// 	int		sol[u->num_paths];
// 	int		tmp;
//
// 	sort_paths(u);
// 	set_paths(u, len);
// 	u->i = -1;
// 	while (++u->i < u->num_paths)
// 		sol[u->i] = 0;
// 	u->i = -1;
// 	while (++u->i < u->num_paths)
// 	{
// 		sol[u->i] = send_waves(u, u->i, len, 0);
// 		// printf("----sol_i: %d----\n", sol[u->i]);
// 		tmp = -1;
// 		while (++tmp < u->num_paths)
// 		{
// 			u->j = -1;
// 			while (++u->j <= len[tmp])
// 			{
// 				u->hm->list[u->paths[tmp][u->j]]->ant_ID = 0;
// 				u->hm->list[u->paths[tmp][u->j]]->has_ant = 0;
// 			}
// 		}
// 	}
// 	find_best_sol(u, sol);
// 	printf("sol: %d (%d)\n", u->min_i, sol[u->min_i]);
// 	send_waves(u, u->min_i, len, 1);
// }

// int		simulate_2(t_struct *u)
// {
// 	int		len[u->num_paths];
// 	int		sol[u->num_paths];
// 	int		tmp;
//
// 	sort_paths(u);
// 	set_paths(u, len);
// 	u->i = -1;
// 	while (++u->i < u->num_paths)
// 		sol[u->i] = 0;
//
// 	int avg_len = 0;
// 	int avg_steps = 0;
// 	int ants_to_send[u->num_paths];
// 	u->i = -1;
// 	while (++u->i < u->num_paths)
// 		avg_len += len[u->i];
// 	avg_len /= u->num_paths;
//
// 	int div_ants = u->ants / u->num_paths;
// 	int ant_rest = u->ants % u->num_paths;
// 	avg_steps = avg_len - 1 + u->ants / u->num_paths;
//
// 	u->i = -1;
// 	while (++u->i < u->num_paths)
// 		ants_to_send[u->i] = avg_steps - len[u->i] + 1;
// 	ants_to_send[0] += ant_rest;
//
// 	u->i = -1;
// 	while (++u->i < u->num_paths)
// 	{
// 		sol[u->i] = send_waves(u, u->i, len, 0, ants_to_send);
// 		// printf("----sol_i: %d----\n", sol[u->i]);
// 		tmp = -1;
// 		while (++tmp < u->num_paths)
// 		{
// 			u->j = -1;
// 			while (++u->j <= len[tmp])
// 			{
// 				u->hm->list[u->paths[tmp][u->j]]->ant_ID = 0;
// 				u->hm->list[u->paths[tmp][u->j]]->has_ant = 0;
// 			}
// 		}
// 	}
// 	find_best_sol(u, sol);
// 	printf("sol: %d (%d)\n", u->min_i, sol[u->min_i]);
// 	send_waves(u, u->min_i, len, 1, ants_to_send);
// }





void	send_ant(t_struct *u, int len[u->num_paths], int ant_pos[u->ants + 1])
{

	u->j = len[u->path_i];
	while (u->j > 0)
	{
		if (u->j == 1 && u->hm->list[u->src]->n_ants > 0)
		{
			--u->hm->list[u->src]->n_ants;
			u->hm->list[u->paths[u->path_i][u->j]]->n_ants = 1;
			u->hm->list[u->paths[u->path_i][u->j]]->ant_ID = u->ants - u->hm->list[u->src]->n_ants;
			ant_pos[u->ants - u->hm->list[u->src]->n_ants] = u->paths[u->path_i][u->j];
			printf("A w: %d	j: %d	ant_ID: %d	ant_pos: %d\n", u->wave, u->j, u->ants - u->hm->list[u->src]->n_ants, ant_pos[u->ants - u->hm->list[u->src]->n_ants]);
		}
		else if (u->j == len[u->path_i] && u->hm->list[u->paths[u->path_i][u->j - 1]]->n_ants != 0)
		{
			if (u->j - 1 == 0) // src
			{
				--u->hm->list[u->src]->n_ants;
				ant_pos[u->ants - u->hm->list[u->src]->n_ants] = u->snk;
				++u->hm->list[u->snk]->n_ants;
				printf("B w: %d	j: %d	ant_ID: %d\n", u->wave, u->j, u->ants - u->hm->list[u->src]->n_ants);
				u->wave++;
			}
			else if (u->j - 1 > 0)
			{
				ant_pos[u->hm->list[u->paths[u->path_i][u->j - 1]]->ant_ID] = u->snk;
				printf("C w: %d	j: %d	ant_ID: %d\n", u->wave, u->j, u->hm->list[u->paths[u->path_i][u->j - 1]]->ant_ID);
				u->hm->list[u->paths[u->path_i][u->j - 1]]->n_ants = 0;
				u->hm->list[u->paths[u->path_i][u->j - 1]]->ant_ID = 0;
				++u->hm->list[u->snk]->n_ants;
				u->wave++;
			}
		}
		else if (u->j > 1 && u->j < len[u->path_i] && u->hm->list[u->paths[u->path_i][u->j - 1]]->n_ants != 0)
		{
			ant_pos[u->hm->list[u->paths[u->path_i][u->j - 1]]->ant_ID] = u->paths[u->path_i][u->j];
			u->hm->list[u->paths[u->path_i][u->j]]->n_ants = 1;
			u->hm->list[u->paths[u->path_i][u->j]]->ant_ID = u->hm->list[u->paths[u->path_i][u->j - 1]]->ant_ID;
			u->hm->list[u->paths[u->path_i][u->j - 1]]->n_ants = 0;
			u->hm->list[u->paths[u->path_i][u->j - 1]]->ant_ID = 0;
			printf("D w: %d	j: %d	ant_ID: %d\n", u->wave, u->j, u->hm->list[u->paths[u->path_i][u->j]]->ant_ID);
		}
		--u->j;
	}
}

void	send_wave(t_struct *u, int a_t_s[u->num_paths],
					int len[u->num_paths], int ant_pos[u->ants + 1])
{
	u->path_i = -1;
	arrived[u->num_paths];

	u->i = -1
	while (u->i u->num_paths)
		arrived[u->i] = 0;
	while (++u->path_i < u->num_paths)
	{
		if (u->wave <= a_t_s[u->path_i])
			send_ant(u, len, ant_pos);
		printf("addas\n");
	}
}

void 	print_step(t_struct *u, int ant_pos[u->ants + 1])
{
	int j;

	j = -1;
	while (++j < u->ants + 1)
		if (ant_pos[j] > 0)
		{
			printf("L%d-%s ", j, u->hm->list[ant_pos[j]]->name);
			if (ant_pos[j] == u->snk)
				ant_pos[j] = 0;
		}
	printf("\n");
}

int		simulate(t_struct *u)
{
	int		len[u->num_paths];
	int		ants_to_send[u->num_paths];
	int		ant_pos[u->ants + 1];
	int		avg_p_len;
	int		avg_p_t;
	int		ants_rest;

	sort_paths(u);
	set_paths(u, len);
	avg_p_len = 0;
	u->i = -1;
	while (++u->i < u->num_paths)
		avg_p_len += len[u->i];
	u->i = -1;
	while (++u->i < u->ants + 1)
		ant_pos[u->i] = -1;
	avg_p_len /= u->num_paths;
	avg_p_t = avg_p_len - 1 + u->ants / u->num_paths;
	ants_rest = u->ants % u->num_paths;
	u->i = -1;
	while (++u->i < u->num_paths)
	{
		ants_to_send[u->i] = -(len[u->i] - 1) + avg_p_t;
		printf("a_t_s[i]: %d\n", ants_to_send[u->i]);
	}
	ants_to_send[0] += ants_rest;
	u->wave = 0;
	u->hm->list[u->src]->n_ants = u->ants;
	u->k = 0;
	while (u->hm->list[u->snk]->n_ants < u->ants)
	{
		send_wave(u, ants_to_send, len, ant_pos);
		print_step(u, ant_pos);
		++u->k;
	}
	printf("len_sol: %d\n", u->k);
}















































void stuff()
{
	;
}
