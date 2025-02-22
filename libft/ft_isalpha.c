/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:52:02 by jbolanho          #+#    #+#             */
/*   Updated: 2024/02/29 17:42:15 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_isalpha(int x)
{
	if ((x >= 65 && x <= 90) || (x >= 97 && x <= 122))
	{
		return (1);
	}
	return (0);
}
