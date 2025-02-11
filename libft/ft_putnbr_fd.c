/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:10:49 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:43:50 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int		nb;
	char			sign;
	char			x;

	nb = n;
	sign = '-';
	if (n < 0)
	{
		write (fd, &sign, 1);
		nb *= -1;
	}
	if (nb < 10)
	{
		x = nb + '0';
		write (fd, &x, 1);
	}
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
}
