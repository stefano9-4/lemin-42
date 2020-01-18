/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:15:01 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:15:02 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_int2(int **tab, int w, int h)
{
	int x;
	int y;

	x = 0;
	while (x < h)
	{
		y = 0;
		while (y < w)
		{
			ft_putnbr(tab[x][y]);
			ft_putchar('\t');
			y++;
		}
		ft_putchar('\n');
		x++;
	}
}
