/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:26:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/24 10:02:16 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	rotate_left(t_data *data, int value)
{
	reset_img(data);
	clear_point(*data);
	clear_line(*data);
	data->grid.x_angle += value;
	if (data->grid.x_angle < 0)
		data->grid.x_angle += 360;
	while (data->grid.x_angle > 360)
		data->grid.x_angle -= 360;
	data->grid.radian_x = (data->grid.x_angle * PI) / 180;
	data->points = parse_points(*data);
	set_colour(data);
	data->lines = get_all_lines(*data);
	render(data);
}

void	rotate_right(t_data *data, int value)
{
	reset_img(data);
	clear_point(*data);
	clear_line(*data);
	data->grid.x_angle -= value;
	if (data->grid.x_angle < 0)
		data->grid.x_angle += 360;
	while (data->grid.x_angle > 360)
		data->grid.x_angle -= 360;
	data->grid.radian_x = (data->grid.x_angle * PI) / 180;
	data->points = parse_points(*data);
	set_colour(data);
	data->lines = get_all_lines(*data);
	render(data);
}