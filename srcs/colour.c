/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/18 10:45:05 by llevasse         ###   ########.fr       */
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
	return (highest * 2);
}

unsigned long	get_rgb(t_line line, int y, int highest_altitude)
{
	double	percent_gradiant;
	int		r;
	int		g;
	int		b;
	int		line_id;

	if (line.altitude_a == 0 && line.altitude_b == 0)
		return (WHITE);
	line_id = line.line_id;
	if (line.y_a > line.y_b)
		y -= line.y_b;
	else
		y -= line.y_a;
	r = HIGHEST_COLOR_R;
	g = HIGHEST_COLOR_G;
	b = HIGHEST_COLOR_B;
	percent_gradiant = (double)y / highest_altitude;
	if (r != 0)
		r = r - ((percent_gradiant * 100));
	if (g != 0)
		g = g - ((percent_gradiant * 100));
	if (b != 0)
		b = b - ((percent_gradiant * 100));
	(void)percent_gradiant;
	(void)line_id;
	return ((r * 256 * 256) + (g * 256) + b);
}