/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:21 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/26 10:14:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_grid	init_grid(void)
{
	struct s_grid	grid;

	grid.wire_len = 50;
	grid.grid_height = WINDOW_HEIGHT / 2;
	grid.grid_width = WINDOW_WIDTH / 2;
	grid.x_angle = 30;
	grid.y_angle = 0;
	grid.grid_z_rotation = 0;
	grid.zoom = 1;
	grid.x_decal = 0;
	grid.y_decal = 0;
	if (grid.x_angle < 0)
		grid.x_angle += 360;
	while (grid.x_angle > 360)
		grid.x_angle -= 360;
	grid.radian_x = ((grid.x_angle * PI) / 180);
	grid.iso_angle = grid.x_angle + 120;
	if (grid.iso_angle < 0)
		grid.iso_angle += 360;
	while (grid.iso_angle > 360)
		grid.iso_angle -= 360;
	grid.iso_radian = (grid.iso_angle * PI) / 180; 
	return (grid);
}

void	reset_grid(t_data *data)
{
	reset_img(data);
	clear_point(*data);
	clear_line(*data);
	data->grid = init_grid();
	data->points = parse_points(*data);
	set_colour(data);
	data->lines = get_all_lines(*data);
	render(data);
}
