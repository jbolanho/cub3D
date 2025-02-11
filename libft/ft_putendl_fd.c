/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:10:46 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:43:46 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int				i;
	char			nl;
	unsigned int	x;

	i = 0;
	nl = '\n';
	x = (unsigned int) fd;
	while (s[i] != '\0')
	{
		write (x, &s[i], 1);
		i++;
	}
	write (x, &nl, 1);
}
