/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:49:49 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/27 13:03:23 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		path_len(t_struct *u, int i)
{
	int len;

	len = -1;
	while (u->paths[i][++len] != u->snk)
		;
	return (len);
}

void	sort_paths(t_struct *u)
{
	int i;
	int *tmp;

	i = -1;
	while (++i + 1 < u->num_paths)
	{
		if (path_len(u, i) > path_len(u, i + 1))
		{
			tmp = u->paths[i];
			u->paths[i] = u->paths[i + 1];
			u->paths[i + 1] = tmp;
			i = -1;
		}
	}
}

void	print_sol(t_struct *u, int n, int len[u->num_paths], int ant_pos[u->i])
{
	int	i;
	int j;
	int id[u->ants];

	i = -1;
	while (++i < u->ants)
		id[i] = 0;
	// i = -1;
	// while (++i <= n)
	// {
		j = -1;
		while (++j < u->ants)
			if (ant_pos[j] >= 0)
			{
				printf("L%d-%s ", j + 1, u->hm->list[ant_pos[j]]->name);
				if (ant_pos[j] == u->snk)
					ant_pos[j] = -1;
			}

	// 	while (++j <= len[i])
	// 		if (u->hm->list[u->paths[i][j]]->ant_ID != 0)
	// 		{
	// 			if (id[u->hm->list[u->paths[i][j]]->ant_ID] != 1)
	// 				printf("L%d-%s ", u->hm->list[u->paths[i][j]]->ant_ID,
	// 					u->hm->list[u->paths[i][j]]->name);
	// 			if (j == len[i])
	// 				id[u->hm->list[u->paths[i][j]]->ant_ID] = 1;
	// 		}
	// }
	printf("\n");
}

void	len_path(t_struct *u)
{
	u->j = 0;
	while (u->paths[u->path_i][++u->j] != u->snk)
		;
}
