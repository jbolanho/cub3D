/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:10:56 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:43:57 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

static size_t	ft_countstr(char const *s, char c)
{
	size_t	countstr;
	int		i;

	countstr = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			countstr++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (countstr);
}

static int	ft_createsub(char **dest, const char *s, char c, int start)
{
	int		i;
	int		end;

	i = 0;
	end = 0;
	while (s[end])
	{
		if (s[end] == c)
			start = end + 1;
		if (s[end] != c && (s[end + 1] == c || s[end + 1] == '\0'))
		{
			dest[i] = (char *)malloc(sizeof(char) * (end - start + 2));
			if (!dest[i])
			{
				free(dest[i]);
				return (0);
			}
			ft_strlcpy(dest[i], (s + start), end - start + 2);
			i++;
		}
		end++;
	}
	dest[i] = (char *) '\0';
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	count;

	count = ft_countstr(s, c);
	if (!s)
		return (NULL);
	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!ft_createsub (arr, s, c, 0))
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}
