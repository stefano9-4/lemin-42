/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:17:51 by lutomasz          #+#    #+#             */
/*   Updated: 2020/02/25 12:50:05 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_snk_src_connected(t_struct *u)
{
	int i;
	int is_snk_connected;
	int is_src_connected;

	i = -1;
	is_src_connected = 0;
	while (++i < u->num_nodes)
		if (u->graph[get_offset_2d(u, u->src, i)] == 1)
		{
			is_src_connected = 1;
			break ;
		}
	is_snk_connected = 0;
	i = -1;
	while (++i < u->num_nodes)
		if (u->graph[get_offset_2d(u, i, u->snk)] == 1)
		{
			is_snk_connected = 1;
			break ;
		}
	return ((is_src_connected == 1 && is_snk_connected == 1) ? 1 : 0);
}

void	find_max_paths(t_struct *u)
{
	int num_src;
	int num_snk;
	int i;

	num_src = 0;
	num_snk = 0;
	i = -1;
	while (++i < u->num_nodes)
	{
		if (u->graph[get_offset_2d(u, u->src, i)] == 1)
			++num_src;
		if (u->graph[get_offset_2d(u, i, u->snk)] == 1)
			++num_snk;
	}
	u->max_paths = (num_src < num_snk) ? num_snk : num_src;
	printf("Max_path: %d\n", u->max_paths);
}

int		*get_bf_path(t_struct *u)
{
	int current;
	int l_path;
	int *bf_path;

	current = u->snk;
	if (u->hm->list[current]->prev == -1)
		return (0);
	l_path = 0;
	while (current != u->src && ++l_path)
	{
		if (l_path > 10000)
			return (0);
		current = u->hm->list[current]->prev;
	}
	bf_path = (int *)malloc(sizeof(int) * 1000);
	current = u->snk;
	u->i = 0;
	bf_path[l_path + 1] = -1;
	while (current != u->src)
	{
		bf_path[l_path - u->i++] = current;
		current = u->hm->list[current]->prev;
	}
	bf_path[0] = u->src;
	return (bf_path);
}

void	print_path(t_struct *u, char *str)
{
	int i;
	int *bf_path;
	int l_path;
	int current;

	bf_path = get_bf_path(u);
	l_path = 0;
	current = u->snk;
	while (current != u->src && ++l_path)
		current = u->hm->list[current]->prev;
	i = -1;
	printf("%s path:\n", str);
	while (++i <= l_path)
		printf("%d(%s) ", bf_path[i], u->hm->list[bf_path[i]]->name);
	printf("\n");
}

int		get_offset_2d(t_struct *u, int x, int y)
{
	return (y * u->num_nodes) + x;
}
