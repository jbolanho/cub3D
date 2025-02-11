/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:43:48 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:44:02 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char) c;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return ((char *)&(str[i]));
		i++;
	}
	if (ch == '\0' && str[i] == '\0')
		return ((char *)&(str[i]));
	return (NULL);
}
