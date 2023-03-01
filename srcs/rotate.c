/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:26:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/03/01 19:47:04 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	rotate_left(t_data *data, int value)
{
	reset_img(data);
	data->grid.angle += value;
	if (data->grid.angle < 0)
		data->grid.angle += 360;
	while (data->grid.angle > 360)
		data->grid.angle -= 360;
	data->grid.radian_x = (data->grid.angle * PI) / 180;
	data->grid.iso_angle = data->grid.angle + 120;
	if (data->grid.iso_angle < 0)
		data->grid.iso_angle += 360;
	while (data->grid.iso_angle > 360)
		data->grid.iso_angle -= 360;
	data->grid.iso_radian = (data->grid.iso_angle * PI) / 180;
	set_point(data);
	set_lines(data);
	set_colour_iso(data);
	render(data);
}

void	rotate_right(t_data *data, int value)
{
	reset_img(data);
	data->grid.angle -= value;
	if (data->grid.angle < 0)
		data->grid.angle += 360;
	while (data->grid.angle > 360)
		data->grid.angle -= 360;
	data->grid.radian_x = (data->grid.angle * PI) / 180;
	data->grid.iso_angle = data->grid.angle + 120;
	if (data->grid.iso_angle < 0)
		data->grid.iso_angle += 360;
	while (data->grid.iso_angle > 360)
		data->grid.iso_angle -= 360;
	data->grid.iso_radian = (data->grid.iso_angle * PI) / 180;
	set_point(data);
	set_lines(data);
	set_colour_iso(data);
	render(data);
}

void	set_lines(t_data *data)
{
	if (!(*data->lines))
		data->lines--;
	while ((*data->lines)->line_id != 0 || !(*data->lines))
	{
		(*data->lines)->x_a = (*data->lines)->point_a->rotated_x;
		(*data->lines)->y_a = (*data->lines)->point_a->rotated_y;
		(*data->lines)->x_b = (*data->lines)->point_b->rotated_x;
		(*data->lines)->y_b = (*data->lines)->point_b->rotated_y;
		(*data->lines)->distance_x = abs((*data->lines)->x_b
				- (*data->lines)->x_a);
		(*data->lines)->distance_y = abs((*data->lines)->y_b
				- (*data->lines)->y_a);
		(*data->lines)->len = (int)sqrt((pow((*data->lines)->distance_y, 2)
					+ pow((*data->lines)->distance_x, 2)));
		data->lines--;
	}
	(*data->lines)->x_a = (*data->lines)->point_a->rotated_x;
	(*data->lines)->y_a = (*data->lines)->point_a->rotated_y;
	(*data->lines)->x_b = (*data->lines)->point_b->rotated_x;
	(*data->lines)->y_b = (*data->lines)->point_b->rotated_y;
	(*data->lines)->distance_x = abs((*data->lines)->x_b - (*data->lines)->x_a);
	(*data->lines)->distance_y = abs((*data->lines)->y_b - (*data->lines)->y_a);
	(*data->lines)->len = (int)sqrt((pow((*data->lines)->distance_y, 2)
				+ pow((*data->lines)->distance_x, 2)));
}

void	set_point(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	if (data->points[0][0] == NULL)
	{
		while (i < data->nb_line)
			data->points[i++] -= data->elem_per_line;
	}
	i = 0;
	while (data->points[i])
	{
		j = 0;
		while (data->points[i][j])
		{
			set_point_follow_up(*data, *(data->points[i][j]), &x, &y);
			data->points[i][j]->rotated_x = x;
			data->points[i][j++]->rotated_y = y;
		}
		i++;
	}
}

void	set_point_follow_up(t_data data, t_point point, int *x, int *y)
{
	int beg_x;
	int beg_y;

	beg_y = data.grid.grid_height - ((data.grid.wire_len * data.grid.zoom)
			* (data.nb_line / 2));
	beg_x = data.grid.grid_width - ((data.grid.wire_len * data.grid.zoom)
			* (data.elem_per_line / 2));
	*y = beg_y + (point.tab_y * (data.grid.wire_len * data.grid.zoom))
		+ data.grid.y_decal;
	*x = beg_x + (point.tab_x * (data.grid.wire_len * data.grid.zoom))
		+ data.grid.x_decal;
	get_rotated_point(data, x, y, point.value);
}