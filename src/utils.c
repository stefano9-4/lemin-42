#include "lemin.h"

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

int	has_space(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == ' ')
			return (1);
	return (0);
}