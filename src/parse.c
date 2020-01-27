/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 09:20:06 by lutomasz          #+#    #+#             */
/*   Updated: 2020/01/27 16:22:02 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	parse(char *av, t_struct *u)
{
	char	*line;
	int		i_id;
	int		cnt;
	//	id is the id of node in u->id
	int		key1;
	int		key2;
	//	store name of room;
	char 	*str;

	i_id = 0;
	cnt = 0;
	u->hm = createHashMap(u->num_nodes);
	get_next_line(u->fd, &line);
	free(line);
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
				;
			str = ft_strndup(line, u->i);
			hm_insert(u->hm, cnt++, str);
		}
		// get connections
		else if (line[0] != '#' && cnt == u->num_nodes)
		{
			while (line[++u->i] != '-')
				;
			u->j = -1;
			key1 = 0;
			while (++u->j < u->num_nodes)
			{
				str = hm_lookup(u->hm, u->j);
				if (ft_strncmp(line, str, u->i) == 0)
					break;
				key1++;
			}
			u->k = -1;
			key2 = 0;
			u->len = ft_strlen(line + u->i + 1);
			while (++u->k < u->num_nodes)
			{
				str = hm_lookup(u->hm, u->k);
				if (ft_strncmp(line + u->i + 1, str, u->len) == 0)
					break;
				++key2;
			}
			u->graph[get_offset_2d(u, key1, key2)] = 1;
			u->graph[get_offset_2d(u, key2, key1)] = 1;
		}
		free(line);
	}
	print_stuff(u);
	u->id[i_id - 1] = '\0';
	return (1);
}

int		set_dimentions(char *av, t_struct *u)
{
	size_t	cnt_char;
	char	*line;

	cnt_char = 0;
	u->num_nodes = 0;
	get_next_line(u->fd, &line);
	free(line);
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
		free(line);
	}
	free(line);
	u->id = ft_strnew(cnt_char + u->num_nodes);
	u->graph = (int*)malloc(sizeof(int) * u->num_nodes * u->num_nodes);
	set_zeros(u, u->num_nodes * u->num_nodes);
	u->coor = (int*)malloc(sizeof(int) * u->num_nodes * u->num_nodes);
	if (!u->id || !u->graph || !u->coor)
		return (0);
	return (1);
}
