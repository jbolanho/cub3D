/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:11:15 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:44:43 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

static int	ft_findset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*mem;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	if (s1 == NULL || set == NULL)
		return (NULL);
	while ((s1[i] != '\0') && ft_findset(s1[start], set))
			start++;
	while (end > start && ft_findset(s1[end - 1], set))
			end--;
	mem = (char *)malloc((end - start) + 1);
	if (mem == NULL)
		return (NULL);
	while (start < end)
	{
		mem[i] = s1[start];
		i++;
		start++;
	}
	mem[i] = '\0';
	return (mem);
}
