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

void	send_waves(t_struct *u, int i)
{
	int		ants_sent;
	int		path_i;
	int		j;
	int		tmp;
	int		ants_arrived;
	int		first;
	int		tmp1;
	
	ants_arrived = 0;
	ants_sent = 0;
	while (!ants_arrived)
	{
		path_i = -1;
		while (++path_i <= i)
		{
			j = 0;
			tmp = ++ants_sent;
			first = 1;
			while (u->paths[path_i][++j])
			{
				if (first)
				{
					u->hm->list[u->paths[path_i][j]]->ant_ID = tmp;
					u->hm->list[u->paths[path_i][j]]->has_ant = 1;
					first = 0;
				}
				else if (u->hm->list[u->paths[path_i][j]]->has_ant == 0)
					u->hm->list[u->paths[path_i][j]]->ant_ID = 0;
				else
				{
					tmp1 = u->hm->list[u->paths[path_i][j]]->ant_ID;
					u->hm->list[u->paths[path_i][j]]->ant_ID = tmp;
					tmp = tmp1;
				}
				if (ants_sent == u->ants)
					ants_sent = 0;
			}
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

	int		sol_found;
	int		i;

	sort_paths(u);
	sol_found = 0;
	i = -1;
	while (++i < u->num_paths)
	{
		send_waves(u, i);
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
