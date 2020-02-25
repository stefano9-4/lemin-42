/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:47:44 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/25 12:51:20 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_graph(t_struct *u)
{
	int i;
	int j;

	i = -1;
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
