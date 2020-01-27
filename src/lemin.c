/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:46:38 by spozzi            #+#    #+#             */
/*   Updated: 2020/01/27 16:02:44 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_all(t_struct *u)
{
	free(u->id);
	free(u->graph);
	free(u->coor);
}

int		main(int ac, char **av)
{
	t_struct	u;

	//u = (t_struct*)malloc(sizeof(t_struct));
	//u.nodes = 5;

	if (ac == 2 && ((u.fd = open(av[1], O_RDONLY)) != 0))
		if (!set_dimentions(av[1], &u))
			printf("ERROR\n");
	close(u.fd);
	if (ac == 2 && ((u.fd = open(av[1], O_RDONLY)) != 0))
		if (!parse(av[1], &u))
			printf("ERROR\n");
	bfs(&u);


	int current = u.snk;
	int l_path = 0;
	while (current != u.src)
	{
		current = u.hm->list[current]->prev;
		++l_path;
	}
	int bfs_path[l_path + 1];
	int i = 0;
	current = u.snk;
	while (current != u.src)
	{
		bfs_path[l_path - i++] = current;
		current = u.hm->list[current]->prev;
	}
	bfs_path[0] = u.src;
	i = -1;
	printf("path:\n");
	while (++i <= l_path)
		printf("%d ", bfs_path[i]);
	printf("\n");

	free_all(&u);
	//u.graph = (int*)malloc(sizeof(int) * u.nodes * u.nodes * 2);
}
