/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/21 00:30:48 by llevasse         ###   ########.fr       */
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
	int		len;
	int		r;
	int		g;
	int		b;

	if (line.altitude_a == 0 && line.altitude_b == 0)
		return ((ZERO_R * 256 * 256) + (ZERO_G * 256) + ZERO_B);
	if (line.z_ratio == 0 && line.altitude_a == data.highest_altitude)
		return ((HIGHEST_R * 256 * 256) + (HIGHEST_G * 256) + HIGHEST_B);
	if (line.z_ratio == 0 && line.altitude_a == data.lowest_altitude)
		return ((LOWEST_R * 256 * 256) + (LOWEST_G * 256) + LOWEST_B);
	len = get_len_with_high_altitude(line, data);
	if (line.altitude_a && line.altitude_a < line.altitude_b)
		i += len / 2;
	if (line.altitude_b && line.altitude_b < line.altitude_a)
		i += len / 2;
	if (line.altitude_a < line.altitude_b)
		percent_gradiant = (double)i / len;
	else
		percent_gradiant = (double)(len - i) / len;
	if (line.z_ratio > 0 && line.altitude_a > line.altitude_b)
		percent_gradiant -= (double)line.altitude_a / data.highest_altitude;
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
		r = BEG_R - ((1 - percent_gradiant) * get_dif(BEG_R, LOWEST_R));
		g = BEG_G - ((1 - percent_gradiant) * get_dif(BEG_G, LOWEST_G));
		b = BEG_B - ((1 - percent_gradiant) * get_dif(BEG_B, LOWEST_B));
	}
	return ((r * 256 * 256) + (g * 256) + b); 
}

int	get_len_with_high_altitude(t_line line, t_data data)
{
	int	dy;
	int	y_a;
	int	y_b;
	int	len;

	y_a = line.y_a;
	if (line.altitude_a != 0)
		y_a *= line.altitude_a / data.highest_altitude;
	if (line.altitude_a != 0 && line.altitude_b > line.altitude_a)
		y_a = line.y_a + line.altitude_a;
	y_b = line.y_b;
	if (line.altitude_b != 0)
		y_b *= data.highest_altitude / line.altitude_b;
	dy = abs(y_b - y_a);
	len = (int)sqrt(pow(dy, 2) + pow(line.distance_x, 2));
	return (len);
}

int	get_dif(int a, int b)
{
	return (a - b);
}
