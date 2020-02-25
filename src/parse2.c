/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:52:12 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/25 12:52:25 by spozzi           ###   ########.fr       */
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
