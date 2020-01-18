/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:14:09 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:14:09 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int x)
{
	return (x >= 0 ? x : -x);
}

static int	ft_get_end(char const *s, int i)
{
	while (s[i])
		i++;
	i--;
	while (((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && (i >= 0)))
		i--;
	i++;
	return (i);
}

char		*ft_strtrim(char const *s)
{
	char	*tab;
	int		start;
	int		end;
	int		i;

	if (s != NULL)
	{
		i = 0;
		while (((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && (s[i])))
			i++;
		start = i;
		end = ft_get_end(s, i);
		if ((tab = (char*)malloc(sizeof(char) * (ft_abs(end - start + 1))))
			== NULL)
			return (NULL);
		i = 0;
		while (s[start] && start < end)
			tab[i++] = s[start++];
		tab[i] = '\0';
		return (tab);
	}
	return (NULL);
}
