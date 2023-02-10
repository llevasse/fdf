/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:55:30 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/10 16:50:14 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char *argv[])
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
 	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	(void)mlx_ptr;
	(void)argc;
	(void)argv;
	return (0);
}
