/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 09:20:06 by lutomasz          #+#    #+#             */
/*   Updated: 2020/01/31 16:25:54 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	source_sink(t_struct *u, char *line, int cnt)
{
	if (ft_strcmp(line, "##start") == 0)
		u->src = cnt;
	else if (ft_strcmp(line, "##end") == 0)
		u->snk = cnt;
}

int		parse_node(t_struct *u, char *line, int *cnt)
{
	char *str;

	u->i = -1;
	while (line[++u->i] != ' ')
		;
	if (!(str = ft_strndup(line, u->i)))
		return (0);
	hm_insert(u->hm, *cnt, str);
	++(*cnt);
	u->i = -1;
	return (1);
}

int		set_keys(t_struct *u, int *key1, int *key2, char *line)
{
	char *str;

	while (++u->j < u->num_nodes)
	{
		str = hm_lookup(u->hm, u->j);
		if (ft_strncmp(line, str, u->i) == 0)
			break ;
		++(*key1);
	}
	while (++u->k < u->num_nodes)
	{
		str = hm_lookup(u->hm, u->k);
		if (ft_strncmp(line + u->i + 1, str, u->len) == 0)
			break ;
		++(*key2);
	}
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
	set_keys(u, &key1, &key2, line);
	u->graph[get_offset_2d(u, key1, key2)] = 1;
	if (key1 != u->snk - 1 && key2 != u->snk)
		u->graph[get_offset_2d(u, key2, key1)] = 1;
	++u->num_edges;
	return (1);
}

int		parse(char *av, t_struct *u)
{
	char	*line;
	int		cnt;

	cnt = 0;
	if (!(u->hm = createHashMap(u->num_nodes)))
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
			parse_links(u, line);
		free(line);
	}
	//print_stuff(u);
	return (1);
}

/*
** dunno if line is freed correctly
*/

int		set_stufff(t_struct *u, char *line)
{
	u->num_edges = 0;
	free(line);
	if (u->num_nodes == 0)
		return (0);
	//u->id = ft_strnew(cnt_char + u->num_nodes);
	u->graph = (int*)malloc(sizeof(int) * u->num_nodes * u->num_nodes);
	set_zeros(u, u->num_nodes * u->num_nodes);
	u->coor = (int*)malloc(sizeof(int) * u->num_nodes * u->num_nodes);
	if (!u->id || !u->graph || !u->coor)
		return (0);
	return (1);
}

int		set_dimentions(char *av, t_struct *u)
{
	char	*line;
	int		ret;

	u->num_nodes = 0;
	ret = get_next_line(u->fd, &line);
	if (ret <= 0 || *line < 1)
		return (0);
	free(line);
	while (get_next_line(u->fd, &line))
	{
		if (!*line)
		{
			free(line);
			return (0);
		}
		if (line[0] != '#' && !has_space(line))
			break ;
		else if (line[0] != '#' && ++u->num_nodes)
			;
		free(line);
	}
	if (!set_stufff(u, line))
		return (0);
	return (1);
}
