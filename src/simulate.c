#include "lemin.h"

int		set_gates(t_struct *u)
{

}

int		set_max_iter(int n)
{
	int r;
	int sol;

	sol = 0;
	r = 0;
	while (++r != n + 1)
		sol += combination(n, r);
}

void	open_paths(t_struct *u, int gates[u->num_paths], int n, int curr)
{
	int tmp[u->num_paths];

}

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

	i = -1;
	while (++i + 1 < u->num_paths)
	{
		if (path_len(u, i) > path_len(u, i + 1))
		{
			int *tmp = u->paths[i];
			u->paths[i] = u->paths[i + 1];
			u->paths[i + 1] = tmp;
			i = -1;
		}
	}
}

void	print_sol(t_struct *u, int n)
{
	int	i;
	int j;

	i = -1;
	while (++i <= n)
	{
		j = 0;
		while (u->paths[i][j] != u->snk)
		{
			j++;
			if (u->hm->list[u->paths[i][j - 1]]->ant_ID != 0)
			{
				printf("(%d/%d): ", i, n);
				printf("L%d-%s ", u->hm->list[u->paths[i][j - 1]]->ant_ID, u->hm->list[u->paths[i][j - 1]]->name);
			}
		}
	}
	printf("\n");
}

void	send_waves(t_struct *u, int i, int len[u->num_paths])
{
	int		ants_sent;
	int		path_i;
	int		j;
	int		ants_arrived;
	int		flag;

	ants_arrived = 0;
	ants_sent = 0;
	flag = 0;
	while (ants_arrived < u->ants)
	{
		path_i = -1;
		while (++path_i <= i)
		{
			//printf("path_i: %d	i: %d	ants_arrived: %d\n", path_i, i, ants_arrived);
			if (ants_sent < u->ants && !flag)
				++ants_sent;
			else
			{
				++flag;
				ants_sent = 0;
				u->hm->list[u->src]->has_ant = 0;
			}
			j = 0;
			while (u->paths[path_i][++j] != u->snk)
				;
			while (u->paths[path_i][j] != u->src)
			{
				if (ants_arrived == u->ants)
					break;
				if (u->paths[path_i][j] == u->snk
						&& u->hm->list[u->paths[path_i][j - 1]]->has_ant == 1)
					++ants_arrived;
				if (u->paths[path_i][j - 1] == u->src && ants_sent != u->ants + 1)
				{
					u->hm->list[u->paths[path_i][j]]->ant_ID = ants_sent;
					u->hm->list[u->paths[path_i][j]]->has_ant = 1;
				}
				if (u->hm->list[u->paths[path_i][j - 1]]->has_ant == 1)
				{
					u->hm->list[u->paths[path_i][j]]->ant_ID = u->hm->list[u->paths[path_i][j - 1]]->ant_ID;
					u->hm->list[u->paths[path_i][j]]->has_ant = 1;
				}
				--j;
			}
		}
		if (ants_arrived != u->ants)
		{
			print_sol(u, i);
		}
	}
}

int		simulate(t_struct *u)
{
	int		gates[u->num_paths];
	int		max_iter;
	int		curr_max;
	int		iter_curr;
	int		num_gates_open;

	int		len[u->num_paths];
	int		sol_found;
	int		i;
	int		j;

	sort_paths(u);
	sol_found = 0;
	i = -1;
	while (++i < u->num_paths)
	{
		j = -1;
		while (u->paths[i][++j] != u->snk)
		{
		 	u->hm->list[u->paths[i][j]]->ant_ID = 0;
			u->hm->list[u->paths[i][j]]->has_ant = 0;
		}
		len[i] = j;
	}
	i = -1;
	while (++i < u->num_paths)
	{
		send_waves(u, i, len);
		printf("------------\n");

	}
	// u->max_paths = u->ants;
	// max_iter = set_max_iter(u->num_paths);
	// num_gates_open = u->num_paths;
	// curr_max = combination(num_gates_open, u->num_paths);
	// iter_curr = 0;
	// i = 0;
	// while (i < max_iter)
	// {
	// 	if (iter_curr == curr_max)
	// 		curr_max = combination(--num_gates_open, u->num_paths);
	// 	open_paths(u, gates, num_gates_open, iter_curr);
	// 	//send_ants(u, gates);
	// 	++iter_curr;
	// }
}