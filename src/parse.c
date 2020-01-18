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

/*
**	get start node and end node infos !!!to do 
*/

int start_or_end(char *line, t_struct *u)
{
	if (ft_strcmp(line + 2, "start"))
		printf("ok\n");
	else if (ft_strcmp(line + 2, "end"))
		printf("end\n");
	return (0);
}

int parse(char *argv, t_struct *u)
{
	int i;
	char *line;

	get_next_line(u->fd, &line);
	while (!ft_isdigit(line[0]))
	{
		free(line);
		get_next_line(u->fd, &line);
	}
	u->ants = ft_atoi(line);
	printf("%d\n", u->ants);
	free(line);
	while (get_next_line(u->fd, &line))
	{
		if (line[0] == '#')
			if (line[1] == '#')
				start_or_end(line, u);
		else
		{
			if (check_node(line, u))
			{
				create_node(u);
				add_node(u);
			}
			else if (node_connection(u))
			{
					create_hash_table(u);
					add_to_list(u);
					free(line);
			}
			else
				break ;
		} 
	}
	while (get_next_line(u->fd, &line))
	{
		if (line[0] == '#')
			free(line);
		else
		{
			if (connection_format(u))
				add_to_hash(u);
			free(line);
		}
	}
	return (1);
}
