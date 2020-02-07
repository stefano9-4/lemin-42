/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_2d_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spozzi <spozzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:28:52 by spozzi            #+#    #+#             */
/*   Updated: 2020/02/07 11:24:43 by spozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		**malloc_2d_int_arr(int **arr, int size_i, int size_j, int value)
{
	int		iter;
	int		j;

	arr = (int**)malloc(sizeof(int*) * size_i);
	iter = -1;
	while (++iter < size_i)
	{
		arr[iter] = (int*)malloc(sizeof(int) * size_j);
		j = -1;
		while (++j < size_j)
			arr[iter][j] = value;
	}
	return (arr);
}
