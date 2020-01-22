/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:38:30 by lutomasz          #+#    #+#             */
/*   Updated: 2020/01/22 13:40:48 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*ptr;

	ptr = NULL;
	if (str != NULL)
	{
		ptr = ft_strnew(n + 1);
		if (ptr == NULL)
			return (NULL);
		ft_strncpy(ptr, str, n);
		ptr[n] = '\0';
	}
	return (ptr);
}
