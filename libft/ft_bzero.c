/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:49:50 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:42:04 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}
