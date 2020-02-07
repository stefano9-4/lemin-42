/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:46:38 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/07 16:09:23 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <time.h>

void	free_all(t_struct *u)
{
	free(u->graph);
	free(u->coor);
}

int		check_and_merge(t_struct *u, int path1, int path2)
{
	int i;
	int j;
	int u1;
	int v1;
	int u2;
	int v2;
	int i_tmp;
	int j_tmp;
	int tmp;

	i = -1;
	while (u->paths[path1][++i + 1] && u->paths[path1][i + 1] != -1)
	{
		u1 = u->paths[path1][i];
		v1 = u->paths[path1][i + 1];
		j = -1;
		while (u->paths[path2][++j] && u->paths[path2][j] != -1)
		{
			u2 = u->paths[path2][j];
			v2 = u->paths[path2][j + 1];
			if (u1 == v2 && v1 == u2)
			{
				i_tmp = i + 2;
				j_tmp = j + 2;
				while (u->paths[path1][i_tmp] != -1 || u->paths[path2][j_tmp] != -1)
				{
					if (u->paths[path2][j_tmp] != -1)
					{
						if (u->paths[path1][i - 1] != u->paths[path2][j_tmp])
							u->paths[path1][i++] = u->paths[path2][j_tmp++];
						else
							j_tmp++;
					}
					if (u->paths[path1][i_tmp] != -1)
					{
						if (u->paths[path1][i_tmp] != u->paths[path2][j - 1])
							u->paths[path2][j++] = u->paths[path1][i_tmp++];
						else
							i_tmp++;
					}
				}
				u->paths[path1][i_tmp] = -1;
				u->paths[path2][j_tmp] = -1;
				return (1);
			}
		}
	}
	return (0);
}

void	merge_path(t_struct *u)
{
	int i;
	int j;
	int i_tmp;
	int j_tmp;
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
	u.edge_list = malloc_2d_int_arr(u.edge_list, u.num_edges, 2, -1);
	u.curr_edg = 0;
	if (ac == 2 && ((u.fd = open(av[1], O_RDONLY)) != 0))
		if (!parse(av[1], &u))
		{
			printf("ERROR 2nd read\n");
			return (0);
		}
	// bfs(&u);
	// print_path(&u, "BFS");
	find_max_paths(&u);
	u.paths = (int**)malloc(sizeof(int*) * u.max_paths);
	start = clock();
	//bfs(&u);
	end = clock();
	printf("RT BFS:	%f\n", (float)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	bellmanFord(&u);
	end = clock();
	printf("RT BF:	%f\n", (float)(end - start) / CLOCKS_PER_SEC);
	u.curr_path = 0;
	u.paths[u.curr_path++] = get_BF_path(&u);
	start = clock();
	printf("AAAAAA\n");
	suurballe(&u);
	printf("asdasd\n");
	int i = -1;
	printf("+=======+\n");
	while (++i < u.curr_path)
	{
		printf("path num %d:\n", i);
		int j = -1;
		while (++j + 1)
		{
			printf("%d(%s) ", u.paths[i][j], u.hm->list[u.paths[i][j]]->name);
			if (u.paths[i][j] == u.snk)
				break ;
		}
		printf("\n");
	}
	printf("+=======+\n");
	if (u.curr_path > 1)
		merge_path(&u);
	i = -1;
	while (++i < u.curr_path)
	{
		printf("path num %d:\n", i);
		int j = -1;
		while (++j + 1)
		{
			printf("%d(%s) ", u.paths[i][j], u.hm->list[u.paths[i][j]]->name);
			if (u.paths[i][j] == u.snk)
				break ;
		}
		printf("\n");
	}
	end = clock();
	printf("RT Suurballe:	%f\n", (float)(end - start) / CLOCKS_PER_SEC);
	free_all(&u);
	//u.graph = (int*)malloc(sizeof(int) * u.nodes * u.nodes * 2);
}
