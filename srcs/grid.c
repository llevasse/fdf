/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:21 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/15 17:34:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_grid	init_grid(void)
{
	struct s_grid	grid;

	grid.wire_len = 30;
	grid.grid_height = WINDOW_HEIGHT / 2;
	grid.grid_width = WINDOW_WIDTH / 2;
	grid.x_angle = 45;
	grid.y_angle = 0;
	grid.grid_z_rotation = 0;
	grid.zoom = 1;

	grid.radian_x = (grid.x_angle * PI) / 180;
	return (grid);
}
