/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:22:28 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:42:48 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*ptrd;
	char	*ptrs;

	ptrd = (char *)dest;
	ptrs = (char *)src;
	i = 0;
	if (!dest && !src)
		return (0);
	if (ptrs < ptrd)
	{
		while (n > 0 && n--)
		{
			ptrd[n] = ptrs[n];
		}
	}
	else
	{
		while (i < n)
		{
		ptrd[i] = ptrs[i];
			i++;
		}
	}
	return (ptrd);
}
