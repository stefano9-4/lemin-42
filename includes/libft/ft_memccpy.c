/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:10:58 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:10:59 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	i = 0;
	c1 = (unsigned char*)dst;
	c2 = (unsigned char*)src;
	while (n--)
	{
		c1[i] = c2[i];
		if (c2[i] == (unsigned char)c)
			return ((void*)c1 + i + 1);
		i++;
	}
	return (NULL);
}
