/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:10:06 by spozzi            #+#    #+#             */
/*   Updated: 2019/12/01 19:10:07 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*tab;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(n) + 1;
	if ((tab = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	if (n == 0)
		tab[0] = '0';
	if (n < 0)
	{
		tab[0] = '-';
		n = -n;
	}
	tab[len - 1] = '\0';
	while (n)
	{
		len--;
		tab[len - 1] = (n % 10) + '0';
		n /= 10;
	}
	return (tab);
}
