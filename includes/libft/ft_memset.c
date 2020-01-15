/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:11:30 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:11:30 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dest;
	unsigned int	i;

	i = 0;
	dest = (unsigned char*)b;
	while (len)
	{
		dest[i] = c;
		i++;
		len--;
	}
	return ((void*)b);
}
