/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 09:20:06 by lutomasz          #+#    #+#             */
/*   Updated: 2020/02/25 13:26:51 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		set_keys(t_struct *u, int *key1, int *key2, char *line)
{
	char	*str;
	int		found;

	found = 0;
	while (++u->j < u->num_nodes)
	{
		str = hm_lookup(u->hm, u->j);
		if (ft_strncmp(line, str, u->i) == 0 && ++found)
			break ;
		++(*key1);
	}
	if (!found)
		return (0);
	found = 0;
	while (++u->k < u->num_nodes)
	{
		str = hm_lookup(u->hm, u->k);
		if (ft_strncmp(line + u->i + 1, str, u->len) == 0 && ++found)
			break ;
		++(*key2);
	}
	if (!found)
		return (0);
	return (1);
}

int		parse_links(t_struct *u, char *line)
{
	int		key1;
	int		key2;
	char	*str;

	u->i = -1;
	while (line[++u->i] != '-' && line[u->i])
		;
	if (!line[u->i] || line[u->i] != '-')
		return (0);
	u->j = -1;
	key1 = 0;
	u->k = -1;
	key2 = 0;
	u->len = ft_strlen(line + u->i + 1);
	if (!set_keys(u, &key1, &key2, line))
		return (0);
	u->graph[get_offset_2d(u, key1, key2)] = 1;
	if (key1 != u->snk - 1 && key2 != u->snk)
		u->graph[get_offset_2d(u, key2, key1)] = 1;
	u->edge_lst[u->curr_edg][0] = key1;
	u->edge_lst[u->curr_edg++][1] = key2;
	return (1);
}

int		parse(char *av, t_struct *u)
{
	char	*line;
	int		cnt;

	cnt = 0;
	if (!(u->hm = create_hash_map(u->num_nodes)))
		return (0);
	get_next_line(u->fd, &line);
	free(line);
	u->ants = -1;
	u->ants = ft_atoi(line);
	if (u->ants <= 0)
		return (0);
	while (get_next_line(u->fd, &line))
	{
		u->i = -1;
		if (line[0] == '#' && line[1] == '#')
			source_sink(u, line, cnt);
		else if (line[0] != '#' && has_space(line))
			parse_node(u, line, &cnt);
		else if (line[0] != '#' && cnt == u->num_nodes)
			if (!parse_links(u, line))
			{
				printf("ERROR: inexistent node\n");
				return (0);
			}
		free(line);
	}
	return (1);
}

/*
** dunno if line is freed correctly
*/

int		set_stufff(t_struct *u, char *line)
{
	free(line);
	if (u->num_nodes == 0)
		return (0);
	u->graph = (int*)malloc(sizeof(int) * u->num_nodes * u->num_nodes);
	set_zeros(u, u->num_nodes * u->num_nodes);
	u->coor = (int*)malloc(sizeof(int) * u->num_nodes * u->num_nodes);
	if (!u->graph || !u->coor)
		return (0);
	return (1);
}

int		set_dimentions(char *av, t_struct *u)
{
	char	*line;
	int		ret;

	u->num_nodes = 0;
	u->num_edges = 0;
	ret = get_next_line(u->fd, &line);
	if (ret <= 0 || *line < 1)
		return (0);
	while (get_next_line(u->fd, &line))
	{
		if (!*line)
		{
			free(line);
			return (0);
		}
		if (line[0] != '#' && !has_space(line))
			++u->num_edges;
		else if (line[0] != '#' && ++u->num_nodes)
			;
	}
	if (!set_stufff(u, line))
		return (0);
	return (1);
}
