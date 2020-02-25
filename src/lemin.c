/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:46:38 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/25 13:43:08 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <time.h>

void	free_all(t_struct *u)
{
	free(u->graph);
	free(u->coor);
}

void	check_and_merge_bis(t_struct *u, int path1, int path2)
{
	u->i_tmp = u->i + 2;
	u->j_tmp = u->j + 2;
	while (u->paths[path1][u->i_tmp] != -1 || u->paths[path2][u->j_tmp] != -1)
	{
		if (u->paths[path2][u->j_tmp] != -1)
		{
			if (u->paths[path1][u->i - 1] != u->paths[path2][u->j_tmp])
				u->paths[path1][u->i++] = u->paths[path2][u->j_tmp++];
			else
				u->j_tmp++;
		}
		if (u->paths[path1][u->i_tmp] != -1)
		{
			if (u->paths[path1][u->i_tmp] != u->paths[path2][u->j - 1])
				u->paths[path2][u->j++] = u->paths[path1][u->i_tmp++];
			else
				u->i_tmp++;
		}
	}
}

int		check_and_merge(t_struct *u, int path1, int path2)
{
	u->i = -1;
	while (u->paths[path1][++u->i + 1] && u->paths[path1][u->i + 1] != -1)
	{
		u->u1 = u->paths[path1][u->i];
		u->v1 = u->paths[path1][u->i + 1];
		u->j = -1;
		while (u->paths[path2][++u->j] && u->paths[path2][u->j] != -1)
		{
			u->u2 = u->paths[path2][u->j];
			u->v2 = u->paths[path2][u->j + 1];
			if (u->u1 == u->v2 && u->v1 == u->u2)
			{
				check_and_merge_bis(u, path1, path2);
				u->paths[path1][u->i_tmp] = -1;
				u->paths[path2][u->j_tmp] = -1;
				return (1);
			}
		}
	}
	return (0);
}

void	merge_path(t_struct *u)
{
	int i;
	int path1;
	int path2;

	i = -1;
	path1 = -1;
	while (++path1 < u->curr_path - 1)
	{
		path2 = path1;
		while (++path2 < u->curr_path)
			if (check_and_merge(u, path1, path2))
				path1 = -1;
	}
}

int		main(int ac, char **av)
{
	t_struct	u;
	time_t start, end;


	if (ac == 2 && ((u.fd = open(av[1], O_RDONLY)) != 0))
		if (!set_dimentions(av[1], &u))
		{
			printf("ERROR 1st read\n");
			return (0);
		}
	close(u.fd);
	u.edge_lst = malloc_2d_int_arr(u.edge_lst, u.num_edges, 2, -1);
	u.curr_edg = 0;
	if (ac == 2 && ((u.fd = open(av[1], O_RDONLY)) != 0))
		if (!parse(av[1], &u) && printf("ERROR 2nd read\n"))
			return (1);
	find_max_paths(&u);
	u.paths = (int**)malloc(sizeof(int*) * u.max_paths);
	// bfs(&u);
	if (!bellman_ford(&u) && printf("Source and Sink not conencted :(\n"))
		return (1);
	u.curr_path = 0;
	u.paths[u.curr_path++] = get_bf_path(&u);
	suurballe(&u);
	int i = -1;
	printf("+=======+\n");
	while (++i < u.curr_path)
	{
		printf("path num %d:\n", i);
		int j = -1;
		while (++j + 1 && printf("%d(%s) ", u.paths[i][j], u.hm->list[u.paths[i][j]]->name))
			if (u.paths[i][j] == u.snk)
				break ;
		printf("\n");
	}
	printf("+=======+\n");
	if (u.curr_path > 1)
		merge_path(&u);
	simulate(&u);
	i = -1;
	while (++i < u.curr_path)
	{
		printf("path num %d:\n", i);
		int j = -1;
		while (++j + 1 && printf("%d(%s) ", u.paths[i][j], u.hm->list[u.paths[i][j]]->name))
			if (u.paths[i][j] == u.snk)
				break ;
		printf("\n");
	}
	free_all(&u);
	return (1);

	//u.graph = (int*)malloc(sizeof(int) * u.nodes * u.nodes * 2);
}
