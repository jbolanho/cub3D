/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:13:53 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/14 17:42:19 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strchr(const char *str, int chr)
// {
// 	size_t	i;

// 	i = 0;
// 	if (chr > 255)
// 	{
// 		chr = chr % 256;
// 	}
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == (unsigned char)chr)
// 			return ((char *)&str[i]);
// 		i++;
// 	}
// 	if (str[i] == chr)
// 		return ((char *)&str[i]);
// 	return (NULL);
// }

char	*ft_strchr(const char *str, int chr)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)chr)
			return ((char *)&str[i]);
		i++;
	}
	if (chr == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
