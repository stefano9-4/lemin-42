/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:13:55 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:13:56 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char *str, char c)
{
	unsigned int i;
	unsigned int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c && str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_words_content(char *str, char c)
{
	char			*tab;
	unsigned int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if ((tab = (char*)malloc(sizeof(char) * (i))) == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

static char	**ft_fill_tab(char **tab, char *str, char c)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] && str[i] != c)
		{
			if ((tab[j] = ft_words_content(str + i, c)) == NULL)
			{
				free(tab);
				return (NULL);
			}
			while (str[i] && str[i] != c)
				i++;
			j++;
		}
		else
			i++;
	}
	tab[j] = 0;
	return (tab);
}

char		**ft_strsplit(char const *s, char c)
{
	char **tab;
	char *str;

	str = (char*)s;
	if (str != NULL)
	{
		if ((tab = (char**)malloc(sizeof(char*) * (ft_words(str, c) + 1)))
			== NULL)
			return (NULL);
		tab = ft_fill_tab(tab, str, c);
		return (tab);
	}
	return (NULL);
}
