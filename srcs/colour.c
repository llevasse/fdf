/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/19 12:50:49 by llevasse         ###   ########.fr       */
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

unsigned int	get_rgb(t_line line, int i, int highest_altitude)
{
	double	percent_gradiant;
	int		r;
	int		g;
	int		b;

	if (line.altitude_a == 0 && line.altitude_b == 0)
		return ((BASIC_R * 256 * 256) + (BASIC_G * 256) + BASIC_B);
	if (line.z_ratio == 0)
		return ((HIGHEST_R * 256 * 256) + (HIGHEST_G * 256) + HIGHEST_B);
	if (line.altitude_a < line.altitude_b)
		percent_gradiant = (double)i / line.len;
	else
		percent_gradiant = (double)(line.len - i) / line.len;
	if (percent_gradiant > 1.0)
		percent_gradiant = 1;
	r = BASIC_R - (percent_gradiant * get_dif(BASIC_R, HIGHEST_R));
	g = BASIC_G - (percent_gradiant * get_dif(BASIC_G, HIGHEST_G));
	b = BASIC_B - (percent_gradiant * get_dif(BASIC_B, HIGHEST_B));
	(void)highest_altitude;
	return ((r * 256 * 256) + (g * 256) + b); 
}

int	get_dif(int a, int b)
{
	return (a - b);
}
