/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/27 17:36:41 by llevasse         ###   ########.fr       */
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
	if (data.points[0][0] == NULL)
	{
		while (x < data.nb_line)
			data.points[x++] -= data.elem_per_line;
	}
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

unsigned int	get_colour(t_line line, int i, t_data data)
{
	int			r;
	int			g;
	int			b;
	t_colour	colour;
	t_colour	colour_2;
	double		gradiant;

	if (line.altitude_a < line.altitude_b)
		gradiant = (double)i / line.len;
	else
		gradiant = (double)(line.len - i) / line.len;
	if (gradiant > 1.0)
		gradiant = 1;
	colour = line.colour_a;
	colour_2 = line.colour_b;
	if (line.z_ratio > 0 && line.altitude_b < 0)
	{
		colour = line.colour_b;
		colour_2 = line.colour_a;
	}
	r =  colour_2.r;
	g =  colour_2.g;
	b =  colour_2.b;
	if (line.z_ratio >= 0)
	{
		r =  colour_2.r - ((1 - gradiant) * get_dif(colour_2.r, colour.r));
		g =  colour_2.g - ((1 - gradiant) * get_dif(colour_2.g, colour.g));
		b =  colour_2.b - ((1 - gradiant) * get_dif(colour_2.b, colour.b));
		if (line.altitude_b < 0 || line.altitude_a == line.altitude_b)
		{
			r =  colour_2.r - ((gradiant) * get_dif(colour_2.r, colour.r));
			g =  colour_2.g - ((gradiant) * get_dif(colour_2.g, colour.g));
			b =  colour_2.b - ((gradiant) * get_dif(colour_2.b, colour.b));		
		}
	}
	else if (line.z_ratio < 0)
	{
		r =  colour_2.r - ((1 - gradiant) * get_dif(colour_2.r, colour.r));
		g =  colour_2.g - ((1 - gradiant) * get_dif(colour_2.b, colour.g));
		b =  colour_2.b - ((1 - gradiant) * get_dif(colour_2.g, colour.b));
		if (line.altitude_b <= 0)
		{
			r =  colour.r - ((1 - gradiant) * get_dif(colour.r, colour_2.r));
			g =  colour.g - ((1 - gradiant) * get_dif(colour.g, colour_2.g));
			b =  colour.b - ((1 - gradiant) * get_dif(colour.b, colour_2.b));		
		}
	}
	if (r < 0)
		r = 0;
	if (r > 255)
		r -= 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g -= 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return ((r * 256 * 256) + (g * 256) + b); 
	(void)data;
}

int	get_rgb(int r, int g, int b)
{
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
		y_a *= (double)line.altitude_a / data.highest_altitude;
	if (line.altitude_a != 0 && line.altitude_b > line.altitude_a)
		y_a = line.y_a + line.altitude_a;
	y_b = line.y_b;
	if (line.altitude_b != 0)
		y_b *= (double)data.highest_altitude / line.altitude_b;
	dy = abs(y_b - y_a);
	len = (int)sqrt(pow(dy, 2) + pow(line.distance_x, 2));
	return (len);
}

int	get_dif(int a, int b)
{
	return (a - b);
}
