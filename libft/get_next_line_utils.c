/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:29:41 by anacaro5          #+#    #+#             */
/*   Updated: 2025/04/03 15:32:26 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_calloc(size_t n_elem, size_t size_bytes)
// {
// 	size_t			total_size;
// 	void			*memory;
// 	size_t			i;
// 	unsigned char	*ptr;

// 	total_size = n_elem * size_bytes;
// 	if (n_elem == 0 || size_bytes == 0)
// 		return (malloc(0));
// 	if (total_size / n_elem != size_bytes)
// 		return (NULL);
// 	memory = malloc(total_size);
// 	if (memory == NULL)
// 		return (NULL);
// 	ptr = (unsigned char *)memory;
// 	i = 0;
// 	while (i < total_size)
// 	{
// 		ptr[i] = 0;
// 		i++;
// 	}
// 	return (memory);
// }

// char	*ft_strchr(const char *str, int chr)
// {
// 	size_t	i;

// 	i = 0;
// 	if (str == NULL)
// 		return (NULL);
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



// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*new;
// 	size_t	len;
// 	size_t	i;
// 	size_t	j;

// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	if (len == 0)
// 		return (NULL);
// 	new = (char *)malloc (len + 1 * sizeof(char));
// 	if (!new)
// 		return (NULL);
// 	i = 0;
// 	while (s1 != NULL && s1[i] != '\0')
// 	{
// 		new[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2 != NULL && s2 [j] != '\0')
// 		new[i++] = s2[j++];
// 	new[i] = '\0';
// 	return (new);
// }

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;

	if (destsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < destsize -1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	if (str == NULL)
// 		return (0);
// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }


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

