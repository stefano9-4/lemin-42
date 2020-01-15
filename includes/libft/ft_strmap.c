/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:13:10 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:13:11 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*tab;
	unsigned int	i;
	unsigned char	*str;

	if (s == NULL || f == NULL)
		return (NULL);
	i = ft_strlen(s);
	str = (unsigned char*)s;
	if ((tab = (char*)malloc(sizeof(char) * i + 1)) == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tab[i] = (*f)(str[i]);
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
