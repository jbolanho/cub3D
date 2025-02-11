/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:11:12 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:44:29 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned
int, char))
{
	int		i;
	int		j;
	char	*mem;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	mem = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (mem == NULL)
		return (NULL);
	while (s[j] != '\0' || j <= i)
	{
		mem[j] = f(j, s[j]);
		j++;
	}
	mem[j] = '\0';
	return (mem);
}
