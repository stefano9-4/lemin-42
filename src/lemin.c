/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:46:38 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/02 13:28:01 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <time.h>

void	free_all(t_struct *u)
{
	free(u->graph);
	free(u->coor);
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
	bfs(&u);
	end = clock();
	printf("RT BFS:	%f\n", (float)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	//bellmanFord(&u);
	end = clock();
	printf("RT BF:	%f\n", (float)(end - start) / CLOCKS_PER_SEC);
	u.curr_path = 0;
	u.paths[u.curr_path++] = get_BF_path(&u);
	// print_path(&u, "BF");
	start = clock();
	suurballe(&u);
	end = clock();
	printf("RT Suurballe:	%f\n", (float)(end - start) / CLOCKS_PER_SEC);
	free_all(&u);
	//u.graph = (int*)malloc(sizeof(int) * u.nodes * u.nodes * 2);
}
