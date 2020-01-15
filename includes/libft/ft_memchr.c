/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:11:11 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:11:13 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			*str;
	size_t			i;

	i = 0;
	str = (char*)s;
	while (n--)
	{
		if (str[i] == (char)c)
			return ((void*)str + i);
		i++;
	}
	return (NULL);
}
