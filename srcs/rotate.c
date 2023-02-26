/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:26:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/26 14:06:19 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	rotate_left(t_data *data, int value)
{
	int	y;
	int	x;
	int	temp_x;
	int	temp_y;

	reset_img(data);
	clear_line(*data);
	data->grid.angle += value;
	if (data->grid.angle < 0)
		data->grid.angle += 360;
	while (data->grid.angle > 360)
		data->grid.angle -= 360;
	data->grid.radian_x = (data->grid.angle * PI) / 180;
	x = 0;
	if (data->points[0][0] == NULL)
	{
		while (x < data->nb_line)
			data->points[x++] -= data->elem_per_line;
	}
	y = 0;
	while (data->points[y])
	{
		x = 0;
		while (data->points[y][x])
		{
			temp_x = ((data->points[y][x]->rotated_x - data->grid.grid_width)
					* cos(data->grid.radian_x) - (data->points[y][x]->rotated_y
						- data->grid.grid_height) * sin(data->grid.radian_x));
			temp_y = ((data->points[y][x]->rotated_x - data->grid.grid_width)
					* sin(data->grid.radian_x) + (data->points[y][x]->rotated_y
						- data->grid.grid_height) * cos(data->grid.radian_x));
			data->points[y][x]->rotated_x = temp_x + data->grid.grid_width;
			data->points[y][x++]->rotated_y = temp_y + data->grid.grid_height;
		}
		y++;
	}
	set_colour(data);
	data->lines = get_all_lines(*data);
	render(data);
}

void	rotate_right(t_data *data, int value)
{
	int	y;
	int	x;
	int	temp_x;
	int	temp_y;

	reset_img(data);
	clear_line(*data);
	data->grid.angle -= value;
	if (data->grid.angle < 0)
		data->grid.angle += 360;
	while (data->grid.angle > 360)
		data->grid.angle -= 360;
	data->grid.radian_x = (data->grid.angle * PI) / 180;
	x = 0;
	if (data->points[0][0] == NULL)
	{
		while (x < data->nb_line)
			data->points[x++] -= data->elem_per_line;
	}
	y = 0;
	while (data->points[y])
	{
		x = 0;
		while (data->points[y][x])
		{
			temp_x = ((data->points[y][x]->rotated_x - data->grid.grid_width)
					* cos(data->grid.radian_x) + (data->points[y][x]->rotated_y
						- data->grid.grid_height) * sin(data->grid.radian_x));
			temp_y = (-(data->points[y][x]->rotated_x - data->grid.grid_width)
					* sin(data->grid.radian_x) + (data->points[y][x]->rotated_y
						- data->grid.grid_height) * cos(data->grid.radian_x));
			data->points[y][x]->rotated_x = temp_x + data->grid.grid_width;
			data->points[y][x++]->rotated_y = temp_y + data->grid.grid_height;
		}
		y++;
	}
	set_colour(data);
	data->lines = get_all_lines(*data);
	render(data);
}

/* 
	rotate around point anti clockwise
	
	float xnew = p.x * c - p.y * s;
	float	ynew = p.x * s + p.y * c;
	
	rotate around point clockwise
	float xnew = p.x * c + p.y * s;
	float	ynew = -p.x * s + p.y * c;
*/