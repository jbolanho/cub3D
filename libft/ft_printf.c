/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:15:46 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:43:25 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_printf.h"

static int	ft_findtype(va_list arg, const char type)
{
	int	i;

	i = 0;
	if (type == 'c')
		i += ft_putchar_pf(va_arg (arg, int));
	else if (type == 's')
		i += ft_putstr_pf(va_arg (arg, char *));
	else if (type == 'p')
		i += ft_print_ptr(va_arg (arg, unsigned long));
	else if (type == 'd')
		i += ft_putnbr_pf(va_arg (arg, int));
	else if (type == 'i')
		i += ft_putnbr_pf(va_arg (arg, int));
	else if (type == 'u')
		i += ft_putunsig(va_arg (arg, unsigned int));
	else if (type == 'x')
		i += ft_print_hex(va_arg (arg, unsigned int), type);
	else if (type == 'X')
		i += ft_print_hex(va_arg (arg, unsigned int), type);
	else if (type == '%')
		i += ft_putperc();
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		narg;
	int		i;

	i = 0;
	narg = 0;
	if (!str)
		return (-1);
	va_start(arg, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			narg += ft_findtype(arg, str[i + 1]);
			i++;
		}
		else
			narg += ft_putchar_pf(str[i]);
		i++;
	}
	va_end(arg);
	return (narg);
}
