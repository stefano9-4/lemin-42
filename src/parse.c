/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 09:20:06 by lutomasz          #+#    #+#             */
/*   Updated: 2020/01/18 09:20:09 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	parse(char *av, t_struct *u)
{
	char	*line;
	int		i_id;
	int		cnt;
	//	id is the id of node in u->id
	int		id1;
	int		id2;

	i_id = 0;
	cnt = 0;
	get_next_line(u->fd, &line);
	u->ants = ft_atoi(line);
	while (get_next_line(u->fd, &line))
	{
		u->i = -1;
		// if ##start or ##end
		if (line[0] == '#' && line[1] == '#')
		{
			if (ft_strcmp(line, "##start") == 0)
				u->src = cnt;
			else if (ft_strcmp(line, "##end") == 0)
				u->snk = cnt;
		}
		// Get node name, X, Y
		else if (line[0] != '#' && has_space(line))
		{
			while (line[++u->i] != ' ')
				u->id[i_id++] = line[u->i];
			u->id[i_id++] = ' ';
			u->coor[cnt] = ft_atoi(line + u->i);
			while (line[++u->i] != ' ')
				;
			u->coor[cnt + u->num_nodes] = ft_atoi(line + u->i);
			cnt++;
		}
		// get connections
		else if (line[0] != '#' && cnt == u->num_nodes)
		{
			while (line[++u->i] != '-')
				;
			u->j = -1;
			id1 = 0;
			while (u->id[++u->j])
			{
				if (ft_strncmp(line, &u->id[u->j], u->i) == 0)
					break;
				while (u->id[++u->j] != ' ' && u->id[u->j])
					;
				id1++;
			}
			u->k = -1;
			id2 = 0;
			u->len = ft_strlen(line + u->i + 1);
			while (u->id[++u->k])
			{
				if (ft_strncmp(line + u->i + 1, &u->id[u->k], u->len) == 0)
					break;
				while (u->id[++u->k] != ' ' && u->id[u->k])
					;
				++id2;
			}
			u->graph[get_offset_2d(u, id1, id2)] = 1;
			u->graph[get_offset_2d(u, id2, id1)] = 1;
		}
	}
	int i = -1;
	printf("ID: %s\n", u->id);
	while (++i < (u->num_nodes))
	{
		int j = -1;
		while (++j < u->num_nodes)
			printf("%d ", u->graph[get_offset_2d(u, i, j)]);
		printf("\n");
	}
	u->id[i_id - 1] = '\0';
}


int set_dimentions(char *av, t_struct *u)
{
	size_t	cnt_char;
	char	*line;

	cnt_char = 0;
	u->num_nodes = 0;
	get_next_line(u->fd, &line);
	while (get_next_line(u->fd, &line))
	{
		if (line[0] != '#' && !has_space(line))
			break;
		else if (line[0] != '#' && ++u->num_nodes)
		{
			u->i = -1;
			while (line[++u->i] != ' ')
				++cnt_char;
		}
	}
	u->id = ft_strnew(cnt_char + u->num_nodes);
	u->graph = (int*)malloc(sizeof(int) * u->num_nodes * u->num_nodes);
	set_zeros(u, u->num_nodes * u->num_nodes);
	u->coor = (int*)malloc(sizeof(int) * u->num_nodes * u->num_nodes);
	if (!u->id || !u->graph || !u->coor)
		return (0);
	return (1);
}

