/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:13:35 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:13:41 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *tab;

	if ((tab = (char*)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	ft_memset(tab, '\0', size + 1);
	return (tab);
}
