/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:15:53 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 14:50:44 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		ft_putchar_pf(char c);
int		ft_putstr_pf(char *s);
int		ft_putnbr_pf(int n);
void	ft_put_hex(unsigned int num, const char type);
int		ft_print_hex(unsigned int num, const char type);
int		ft_print_ptr(unsigned long nb);
int		ft_putperc(void);
int		ft_putunsig(unsigned int n);
char	*ft_itoa_pf(int n);
char	*ft_uitoa(unsigned int n);
char	*ft_strdup_pf(const char *s);

#endif