/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:12:46 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:12:46 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char*)s1;
	c2 = (unsigned char*)s2;
	i = 0;
	if (c1 != NULL && c2 != NULL)
	{
		while (c1[i] && c1[i] == c2[i])
			i++;
		if ((c1[i] - c2[i]) != 0)
			return (0);
		return (1);
	}
	return (0);
}
