/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:02:30 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:43:18 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_printf.h"

static int	ft_ptr_len(unsigned long num)
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

static void	ft_put_ptr(unsigned long num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_pf((num + '0'));
		else
			ft_putchar_pf((num - 10 + 'a'));
	}
}

int	ft_print_ptr(unsigned long ptr)
{
	int	i;

	i = 2;
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	else
	{
		write(1, "0x", 2);
		ft_put_ptr(ptr);
		i += ft_ptr_len(ptr);
	}
	return (i);
}
