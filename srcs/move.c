/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:49:07 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/24 10:02:16 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	move_left(t_data *data, int value)
{
	reset_img(data);
	clear_point(*data);
	clear_line(*data);
	data->grid.x_decal += value;
	data->points = parse_points(*data);
	set_colour(data);
	data->lines = get_all_lines(*data);
	render(data);
}

void	move_right(t_data * data, int value)
{
	reset_img(data);
	clear_point(*data);
	clear_line(*data);
	data->grid.x_decal -= value;
	data->points = parse_points(*data);
	set_colour(data);
	data->lines = get_all_lines(*data);
	render(data);
}

void	move_up(t_data *data, int value)
{
	reset_img(data);
	clear_point(*data);
	clear_line(*data);
	data->grid.y_decal += value;
	data->points = parse_points(*data);
	set_colour(data);
	data->lines = get_all_lines(*data);
	render(data);
}

void	move_down(t_data * data, int value)
{
	reset_img(data);
	clear_point(*data);
	clear_line(*data);
	data->grid.y_decal -= value;
	data->points = parse_points(*data);
	set_colour(data);
	data->lines = get_all_lines(*data);
	render(data);
}

