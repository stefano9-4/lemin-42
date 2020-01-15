/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:12:19 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:12:20 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char			*c2;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	c2 = (char*)s2;
	while (s1[i])
		i++;
	while (c2[j])
	{
		s1[i + j] = c2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}
