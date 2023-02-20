/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/20 12:08:00 by llevasse         ###   ########.fr       */
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

int	get_lowest_altitude(t_data data)
{
	int	x;
	int	y;
	int	lowest;
	
	y = 0;
	x = 0;
	lowest = 0;
	while (data.points[y])
	{
		x = 0;
		while (data.points[y][x])
		{
			if (lowest > data.points[y][x]->value)
				lowest = data.points[y][x]->value;
			x++;
		}
		y++;	
	}
	return (lowest * 2);
}

unsigned int	get_rgb(t_line line, int i, t_data data)
{
	double	percent_gradiant;
	int		r;
	int		g;
	int		b;

	if (line.altitude_a == 0 && line.altitude_b == 0)
		return ((ZERO_R * 256 * 256) + (ZERO_G * 256) + ZERO_B);
	if (line.z_ratio == 0 && line.altitude_a == data.highest_altitude)
		return ((HIGHEST_R * 256 * 256) + (HIGHEST_G * 256) + HIGHEST_B);
	if (line.z_ratio == 0 && line.altitude_a == data.lowest_altitude)
		return ((LOWEST_R * 256 * 256) + (LOWEST_G * 256) + LOWEST_B);
	if (line.altitude_a < line.altitude_b)
		percent_gradiant = (double)i / line.len;
	else
		percent_gradiant = (double)(line.len - i) / line.len;
	if (percent_gradiant > 1.0)
		percent_gradiant = 1;
	if (line.z_ratio > 0)
	{
		r = BEG_R - (percent_gradiant * get_dif(BEG_R, HIGHEST_R));
		g = BEG_G - (percent_gradiant * get_dif(BEG_G, HIGHEST_G));
		b = BEG_B - (percent_gradiant * get_dif(BEG_B, HIGHEST_B));
	}
	else
	{
		r = BEG_R - (percent_gradiant * get_dif(BEG_R, LOWEST_R));
		g = BEG_G - (percent_gradiant * get_dif(BEG_G, LOWEST_G));
		b = BEG_B - (percent_gradiant * get_dif(BEG_B, LOWEST_B));
	}
	return ((r * 256 * 256) + (g * 256) + b); 
}

int	get_dif(int a, int b)
{
	return (a - b);
}
