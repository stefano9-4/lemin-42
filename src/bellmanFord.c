#include "lemin.h"

void FinalSolution(int dist[], int n)
{
	// This function prints the final solution
	printf("\nVertex\tDistance from Source Vertex\n");
	int i;

	for (i = 0; i < n; ++i){
		printf("%d \t\t %d\n", i, dist[i]);
	}
}

void bellmanFord(t_struct *u)
{
	int		dist[u->num_nodes];
	int		i;
	int		j;
	int		i_rel;
	int		is_updt;
	int		weight;
	int		weight2;

	i = -1;
	while (++i < u->num_nodes)
		dist[i] = INT_MAX;
	dist[u->src] = 0;
	i_rel = -1;
	// Relax edges |V - 1| times
	while (++i_rel < u->num_nodes - 1)
	{
		i = -1;
		is_updt = 0;
		while (++i < u->num_edges && u->edge_list[i][0] != -1
				&& u->edge_list[i][1] != -1)
		{
			weight = u->graph[get_offset_2d(u, u->edge_list[i][0], u->edge_list[i][1])];
			weight2 = u->graph[get_offset_2d(u, u->edge_list[i][1], u->edge_list[i][0])];
			if (weight != 0)
				if ((double)dist[u->edge_list[i][0]] + (double)weight < dist[u->edge_list[i][1]] && ++is_updt)
				{
					dist[u->edge_list[i][1]] = dist[u->edge_list[i][0]] + weight;
					u->hm->list[u->edge_list[i][1]]->prev = u->edge_list[i][0];
				}
			if (weight2 != 0)
				if ((double)dist[u->edge_list[i][1]] + (double)weight2 < (double)dist[u->edge_list[i][0]] && ++is_updt)
				{
					dist[u->edge_list[i][0]] = dist[u->edge_list[i][1]] + weight2;
					u->hm->list[u->edge_list[i][0]]->prev = u->edge_list[i][1];
				}
		}
		// If no change is made just stop
		if (is_updt == 0)
			break;
	}

	//Check negative edges cycle
	// i = -1;
	// while (++i < u->num_nodes)
	// {
	// 	j = -1;
	// 	while (++j < u->num_nodes)
	// 	{
	// 		weight = u->graph[get_offset_2d(u, i, j)];
	// 		if (weight != 0)
	// 			if (dist[i] + weight < dist[j])
	// 				printf("This graph contains negative edge cycle\n");
	// 	}
	// }

	//FinalSolution(dist, u->num_nodes);
}
