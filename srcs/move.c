/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:49:07 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/28 11:01:33 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	move_left(t_data *data, int value)
{
	reset_img(data);
	data->grid.x_decal += value;
	set_point(data);
	set_colour(data);
	set_lines(data);
	render(data);
}

void	move_right(t_data * data, int value)
{
	reset_img(data);
	data->grid.x_decal -= value;
	set_point(data);
	set_colour(data);
	set_lines(data);
	render(data);
}

void	move_up(t_data *data, int value)
{
	reset_img(data);
	data->grid.y_decal += value;
	set_point(data);
	set_colour(data);
	set_lines(data);
	render(data);
}

void	move_down(t_data * data, int value)
{
	reset_img(data);
	data->grid.y_decal -= value;
	set_point(data);
	set_colour(data);
	set_lines(data);
	render(data);
}

