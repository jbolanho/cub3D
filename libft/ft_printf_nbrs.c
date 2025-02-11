/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbrs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:36:53 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:43:11 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_printf.h"

int	ft_putnbr_pf(int n)
{
	char	*num;
	int		i;

	i = 0;
	num = ft_itoa_pf(n);
	if (num == NULL)
	{
		ft_putstr_pf("(null)");
		return (6);
	}
	while (num[i])
	{
		write(1, &num[i], 1);
		i++;
	}
	free(num);
	return (i);
}

int	ft_putunsig(unsigned int n)
{
	char	*num;
	int		i;

	i = 0;
	num = ft_uitoa(n);
	if (num == NULL)
	{
		ft_putstr_pf("(null)");
		return (6);
	}
	while (num[i])
	{
		write(1, &num[i], 1);
		i++;
	}
	free(num);
	return (i);
}

static int	ft_sizeunnb(unsigned int n)
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

char	*ft_uitoa(unsigned int n)
{
	long	nb;
	long	i;
	char	*str;

	nb = (long)n;
	if (n < 0)
		nb *= -1;
	i = (ft_sizeunnb(n));
	if (n == 0)
		return (ft_strdup_pf("0"));
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
