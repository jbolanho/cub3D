/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:13:02 by jbolanho          #+#    #+#             */
/*   Updated: 2025/02/12 15:47:17 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	main(int argc, char **argv)
{
	t_game	*cub;

	init(&cub);
	validate(&cub, argv[1]);
	game(&cub, argv[1]);
	bye_bye(&cub);
	return (0);
}
