/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:32:45 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:44:59 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/get_next_line.h"

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		t;
	char	*mem;

	i = 0;
	j = 0;
	t = 0;
	mem = (char *)malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!mem)
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

char	*ft_strchr_gnl(const char *str, int c)
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

char	*ft_strdup_gnl(const char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	str = (char *)malloc((i + 1) * sizeof(char));
	if (str == NULL)
	{
		free(str);
		return (NULL);
	}
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char			*mem;
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	if (start > (unsigned int)ft_strlen_gnl(s) || len == 0)
		return (ft_strdup_gnl(""));
	if (ft_strlen_gnl(s + start) < (int)len)
		len = ft_strlen_gnl(s + start);
	mem = (char *)malloc((len + 1) * sizeof(char));
	if (mem == NULL)
	{
		free(mem);
		return (NULL);
	}
	while (s[start + i] != '\0' && i < len)
	{
		mem[i] = s[start + i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
