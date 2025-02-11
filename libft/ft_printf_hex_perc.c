/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_perc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:33:12 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:42:58 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_printf.h"

int	ft_putperc(void)
{
	write (1, "%", 1);
	return (1);
}

static int	ft_hex_len(unsigned	int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	ft_put_hex(unsigned int num, const char type)
{
	if (num >= 16)
	{
		ft_put_hex(num / 16, type);
		ft_put_hex(num % 16, type);
	}
	else
	{
		if (num <= 9)
			ft_putchar_pf((num + '0'));
		else
		{
			if (type == 'x')
				ft_putchar_pf((num - 10 + 'a'));
			if (type == 'X')
				ft_putchar_pf((num - 10 + 'A'));
		}
	}
}

int	ft_print_hex(unsigned int num, const char type)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_put_hex(num, type);
	return (ft_hex_len(num));
}
