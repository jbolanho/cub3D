/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:11:04 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:44:13 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		t;
	char	*mem;

	i = 0;
	j = 0;
	t = 0;
	mem = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (mem == NULL)
		return (NULL);
	while (s1[i] != 0)
	{
		mem[t] = s1[i];
		i++;
		t++;
	}
	while (s2[j] != 0)
	{
		mem[t] = s2[j];
		j++;
		t++;
	}
	mem[t] = '\0';
	return (mem);
}
