/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:13:02 by jbolanho          #+#    #+#             */
/*   Updated: 2025/02/25 15:14:53 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	main(int argc, char **argv)
{
	t_game	cub;

	// validate(argc, argv, &cub);
	(void)argc;
	(void)argv;
	init(&cub);
	game(&cub);
	//bye_bye(&cub);
	return (EXIT_SUCCESS);
}
