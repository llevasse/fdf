/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:21 by llevasse          #+#    #+#             */
/*   Updated: 2023/03/01 19:47:04 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_grid	init_grid(void)
{
	struct s_grid	grid;

	grid.wire_len = 50;
	grid.grid_height = WINDOW_HEIGHT / 2;
	grid.grid_width = WINDOW_WIDTH / 2;
	grid.angle = 30;
	grid.grid_z_rotation = 0;
	grid.zoom = 1;
	grid.x_decal = 0;
	grid.y_decal = 0;
	if (grid.angle < 0)
		grid.angle += 360;
	while (grid.angle > 360)
		grid.angle -= 360;
	grid.radian_x = ((grid.angle * PI) / 180);
	grid.iso_angle = grid.angle + 120;
	if (grid.iso_angle < 0)
		grid.iso_angle += 360;
	while (grid.iso_angle > 360)
		grid.iso_angle -= 360;
	grid.iso_radian = (grid.iso_angle * PI) / 180;
	/* parametter to determine the position of Z
	z_amplifier = grid.wire_len | less visually pleasing but respect the measure 
	z_amplifier = 1 | more visually pleasing but don't respect the measure*/
	grid.z_amplifier = 1;
	return (grid);
}

void	reset_grid(t_data *data)
{
	reset_img(data);
	clear_point(*data);
	clear_line(*data);
	data->grid = init_grid();
	data->points = parse_points(*data);
	set_colour_iso(data);
	data->lines = get_all_lines(*data);
	render(data);
	ft_printf("reset grid!\n");
}
