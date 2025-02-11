/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:43:55 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:44:16 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t s)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = (ft_strlen(dest));
	slen = (ft_strlen(src));
	i = 0;
	if (dlen >= s)
		return (s + slen);
	while (dlen + i < s - 1 && src[i] != '\0')
	{
		dest[dlen + i] = src[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (dlen + slen);
}
