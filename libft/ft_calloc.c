/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:42:20 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:42:08 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*mem;
	size_t	total_size;

	total_size = n * size;
	if (n && size && n != total_size / size)
		return (NULL);
	mem = malloc(total_size);
	if (mem == NULL)
		return (NULL);
	if (mem)
		ft_bzero(mem, total_size);
	return (mem);
}
