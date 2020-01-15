/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:13:43 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:13:44 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*s1;
	char	*s2;
	size_t	i;
	size_t	j;

	s1 = (char*)haystack;
	s2 = (char*)needle;
	i = 0;
	if (!(s2[0]))
		return (s1);
	while (s1[i])
	{
		j = 0;
		while ((s1[i + j] && s1[i + j] == s2[j]) && i + j < len)
			j++;
		if (s2[j] == '\0')
			return (s1 + i);
		i++;
	}
	return (NULL);
}
