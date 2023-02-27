/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:26:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/27 12:19:05 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	rotate_left(t_data *data, int value)
{
	reset_img(data);
 	clear_point(*data);
	clear_line(*data);
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
	data->points = parse_points(*data);

/* 	rotate_clockwise(data);
 */
	set_colour(data);
	data->lines = get_all_lines(*data);
	render(data);
}

void	rotate_right(t_data *data, int value)
{
	reset_img(data);
 	clear_point(*data);
	clear_line(*data);
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
	data->points = parse_points(*data);

/* 	rotate_anticlockwise(data);
 */
	set_colour(data);
	data->lines = get_all_lines(*data);
	render(data);
}

void	rotate_clockwise(t_data *data)
{
	int	y;
	int	x;
	int	temp_x;
	int	temp_y;

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
		if (y == 0)
			x = 1;
		while (data->points[y][x])
		{
			temp_x = ((double)(data->points[y][x]->rotated_x - data->grid.grid_width)
					* cos(data->grid.radian_x) + (double)(data->points[y][x]->rotated_y
						- data->grid.grid_height) * sin(data->grid.radian_x));
			temp_y = ((double)-(data->points[y][x]->rotated_x - data->grid.grid_width)
					* sin(data->grid.radian_x) + (double)(data->points[y][x]->rotated_y
						- data->grid.grid_height) * cos(data->grid.radian_x));
			data->points[y][x]->rotated_x = temp_x + data->grid.grid_width;
			data->points[y][x++]->rotated_y = temp_y + data->grid.grid_height;
		}
		y++;
	}
}
void	rotate_anticlockwise(t_data *data)
{
	int	y;
	int	x;
	int	temp_x;
	int	temp_y;

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
		if (y == 0)
			x = 1;
		while (data->points[y][x])
		{
			temp_x = (((double)(data->points[y][x]->rotated_x - data->grid.grid_width)
					* cos(data->grid.radian_x)) - ((double)(data->points[y][x]->rotated_y
						- data->grid.grid_height) * sin(data->grid.radian_x)));
			temp_y = (((double)(data->points[y][x]->rotated_x - data->grid.grid_width)
					* sin(data->grid.radian_x)) + ((double)(data->points[y][x]->rotated_y
						- data->grid.grid_height) * cos(data->grid.radian_x)));
			data->points[y][x]->rotated_x = temp_x + data->grid.grid_width;
			data->points[y][x++]->rotated_y = temp_y + data->grid.grid_height;
		}
		y++;
	}
}

/* 
Using your function prototype: (x, y) -> (p.x, p.y); (a, b) -> (cx, cy); theta
	-> angle:

POINT	rotate_point(float cx, float cy, float angle, POINT p){

     return POINT(cos(angle) * (p.x - cx) - sin(angle) * (p.y - cy) + cx,
                  sin(angle) * (p.x - cx) + cos(angle) * (p.y - cy) + cy);
}


	rotate around point anti clockwise
	
	xnew = ((point_x - origin_x) * COSINUS_ANGLE) - ((point_y - origin_y)
			* SINUS_ANGLE) + origin_x;
	ynew = ((point_x - origin_x) * SINUS_ANGLE) - ((point_y - origin_y)
			* COSINUS_ANGLE) + origin_Y;
	ynew = p.x * s + p.y * c;
	
	rotate around point clockwise
	xnew = ((point_x - origin_x) * COSINUS_ANGLE) + ((point_y - origin_y)
			* SINUS_ANGLE) + origin_x;
	ynew = (-(point_x - origin_x) * SINUS_ANGLE) + ((point_y - origin_y)
			* COSINUS_ANGLE) + origin_Y;
*/