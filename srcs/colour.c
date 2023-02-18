/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/18 15:37:24 by llevasse         ###   ########.fr       */
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
		return ((BASIC_R * 256 * 256) + (BASIC_G * 256) + BASIC_B);
	line_id = line.line_id;
	if (line.y_a > line.y_b)
		y -= line.y_b;
	else
		y -= line.y_a;
	if (y == 0)
		return ((HIGHEST_R * 256 * 256) + (HIGHEST_G * 256) + HIGHEST_B);
	percent_gradiant = (double)y / highest_altitude;
	r = BASIC_R - ((percent_gradiant * 100) * get_dif(BASIC_R, HIGHEST_R));
	g = BASIC_G - ((percent_gradiant * 100) * get_dif(BASIC_G, HIGHEST_G));
	b = BASIC_B - ((percent_gradiant * 100) * get_dif(BASIC_B, HIGHEST_B));
	(void)percent_gradiant;
	(void)line_id;
	return ((r * 256 * 256) + (g * 256) + b);
}

int	get_dif(int a, int b)
{
	return (a - b);
}