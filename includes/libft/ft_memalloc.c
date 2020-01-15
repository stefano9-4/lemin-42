/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:10:47 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:10:55 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *tab;

	tab = NULL;
	if (size > 0)
	{
		if ((tab = (void*)malloc(sizeof(void) * size)) == NULL)
			return (NULL);
		ft_bzero(tab, size);
		return (tab);
	}
	return (tab);
}
