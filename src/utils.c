/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:17:51 by lutomasz          #+#    #+#             */
/*   Updated: 2020/02/02 15:22:09 by spozzi           ###   ########.fr       */
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

int		*get_BF_path(t_struct *u)
{
	int current;
	int l_path;
	int i;
	int *bf_path;

	current = u->snk;
	l_path = 0;
	if (u->hm->list[current]->prev == -1)
		return (0);
	// printf("aaaa\n");
	while (current != u->src && ++l_path)
	{
		current = u->hm->list[current]->prev;
		// printf("%d (%s)\n", current, u->hm->list[current]->name);
	}
	// printf("qwdd\n");
	bf_path = (int *)malloc(sizeof(int) * l_path - 1);
	current = u->snk;
	i = 0;
	while (current != u->src)
	{
		bf_path[l_path - i++] = current;
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

	bf_path = get_BF_path(u);
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

int		get_offset_3d(t_struct u, int x, int y, int z)
{
	return (z * u.num_nodes * u.num_nodes) + (y * u.num_nodes) + x;
}

int		get_offset_2d(t_struct *u, int x, int y)
{
	return (y * u->num_nodes) + x;
}

void	print_graph(t_struct *u)
{
	int i = -1;
	int j;

	printf("ID: %s\n", u->id);
	while (++i < (u->num_nodes))
	{
		j = -1;
		while (++j < u->num_nodes)
			printf("%d ", u->graph[get_offset_2d(u, i, j)]);
		printf("\n");
	}
}

void	set_zeros(t_struct *u, int size)
{
	int i;

	i = -1;
	while (++i < size)
		u->graph[i] = 0;
}

int		has_space(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == ' ')
			return (1);
	return (0);
}

void	print_stuff(t_struct *u)
{
	int aa;
	int i;
	int j;
	int print_hMap = 1;
	int print_graph = 1;

	if (print_hMap)
	{
		aa = -1;
		printf("HashMap values:\n");
		while (++aa < u->num_nodes)
		{
			int pos = hashCode(u->hm, aa);
			printf("key:		%d\n", u->hm->list[pos]->key);
			printf("name:		%s\n", u->hm->list[pos]->name);
			printf("prev:		%d\n", u->hm->list[pos]->prev);
			printf("has_ant:	%d\n", u->hm->list[pos]->has_ant);
			printf("isVisited:	%d", u->hm->list[pos]->isVisited);
			if (aa != u->num_nodes - 1)
				printf("\n\n");
			// printf("%s ", hm_lookup(u->hm, aa));
		}
		printf("\n\n-------------------\n\n");
	}
	if (print_graph)
	{
		i = -1;
		printf("Graph:\n");
		while (++i < (u->num_nodes))
		{
			j = -1;
			while (++j < u->num_nodes)
				printf("%d ", u->graph[get_offset_2d(u, i, j)]);
			printf("\n");
		}
		printf("Source (k, n):	(%d, %s)\n", u->src, u->hm->list[hashCode(u->hm, u->src)]->name);
		printf("Sink   (k, n):	(%d, %s)\n", u->snk, u->hm->list[hashCode(u->hm, u->snk)]->name);
		printf("\n-------------------\n");
	}
}
