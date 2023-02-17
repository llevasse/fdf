/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/17 23:30:45 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_highest_altitude(t_data data)
{
	int	x;
	int	y;
	int	highest;
	
	y = 0;
	x = 0;
	highest = 0;
	while (x < data.nb_line)
		data.points[x++] -= data.elem_per_line;
	while (data.points[y])
	{
		x = 0;
		while (data.points[y][x])
		{
			if (highest < data.points[y][x]->value)
				highest = data.points[y][x]->value;
			x++;
		}
		y++;	
	}
	return (highest);
}

unsigned long	get_rgb(t_line line, int y, int highest_altitude)
{
	double	percent_gradiant;
	int	r;
	int	g;
	int	b;

	if (line.altitude_a == 0 && line.altitude_b == 0)
		return (WHITE);
	if (line.y_a > line.y_b)
		y -= line.y_b;
	else
		y -= line.y_a;
	percent_gradiant = y / highest_altitude;
	r = HIGHEST_COLOR_R - ((percent_gradiant * 100));
	g = HIGHEST_COLOR_G - ((percent_gradiant * 100));
	b = HIGHEST_COLOR_B - ((percent_gradiant * 100));
	(void)percent_gradiant;
	return ((r * 256 * 256) + (g * 256) + b);
}