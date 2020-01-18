/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:13:59 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:14:00 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char			*s1;
	char			*s2;
	unsigned int	i;
	unsigned int	j;

	s1 = (char*)haystack;
	s2 = (char*)needle;
	i = 0;
	if (!(s2[0]))
		return (s1);
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] && s1[i + j] == s2[j])
			j++;
		if (s2[j] == '\0')
			return (s1 + i);
		i++;
	}
	return (NULL);
}
