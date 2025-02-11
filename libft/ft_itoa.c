/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:10:32 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:42:32 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

static int	ft_sizenb(int n)
{
	int		size;

	size = 0;
	if (n < 0)
	{
		size = 1;
	}
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nb;
	long	i;
	char	*str;

	nb = (long)n;
	if (n < 0)
		nb *= -1;
	i = (ft_sizenb(n));
	if (n == 0)
		return (ft_strdup("0"));
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (i > 0)
	{
		str[i - 1] = '0' + (nb % 10);
		nb /= 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
