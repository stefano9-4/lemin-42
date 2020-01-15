/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:13:47 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:13:49 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	unsigned int	i;
	char			*str1;

	str1 = NULL;
	str = (char*)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			str1 = &str[i];
		i++;
	}
	if (str[i] == (char)c)
		str1 = &str[i];
	return (str1);
}
