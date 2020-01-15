/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab2_cpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:15:06 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:15:07 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**tab2_cpy(char **src)
{
	int		i;
	int		len;
	char	**tab;

	len = 0;
	while (src[len])
		len++;
	tab = (char**)malloc(sizeof(char*) * len + 1);
	i = -1;
	while (++i < len)
		tab[i] = ft_strdup(src[i]);
	tab[i] = 0;
	return (tab);
}
