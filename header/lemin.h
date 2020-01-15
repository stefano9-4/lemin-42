/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:51:42 by spozzi            #+#    #+#             */
/*   Updated: 2020/01/14 12:43:04 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIMIN_H
# define FILLER_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_struct
{
	int		*graph;
	int		src[2];
	int		snk[2];
	int		*dist;
	int		*prev;
	int		*q;
	int		i;
	int		v;
}				t_struct;
