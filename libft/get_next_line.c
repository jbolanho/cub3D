/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:32:39 by jbolanho          #+#    #+#             */
/*   Updated: 2024/03/07 14:21:19 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/get_next_line.h"

static char	*ft_read_file(int fd, char *buff, char *txt)
{
	int		size;
	char	*temp;

	size = 1;
	while (size != '\0')
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == -1)
			return (NULL);
		else if (size == 0)
			break ;
		buff[size] = '\0';
		if (!txt)
			txt = ft_strdup_gnl("");
		temp = txt;
		txt = ft_strjoin_gnl(temp, buff);
		free(temp);
		temp = NULL;
		if (ft_strchr_gnl(buff, '\n'))
			break ;
	}
	return (txt);
}

static char	*ft_line(char *line)
{
	char	*txt;
	int		i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (0);
	txt = ft_substr_gnl(line, i + 1, ft_strlen_gnl(line) - i);
	if (*txt == '\0')
	{
		free (txt);
		txt = NULL;
	}
	line[i + 1] = '\0';
	return (txt);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*txt;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (0);
	line = ft_read_file(fd, buff, txt);
	free(buff);
	if (!line)
	{
		if (txt != NULL)
		{
			free (txt);
			txt = NULL;
		}
		return (NULL);
	}
	txt = ft_line(line);
	return (line);
}
