/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:55:39 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/24 10:32:57 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point	***parse_points(t_data data)
{
	int				i;
	int				j;
	t_point			***points;

	points = malloc((data.nb_line + 1) * sizeof(t_point));
	if (!points)
		return (NULL);
	i = 0;
	while (i < data.nb_line)
	{
		j = 0;
		points[i] = malloc((data.elem_per_line + 1) * sizeof(t_point));
		if (!points[i])
			return (clear_point(data), NULL);
		while (j < data.elem_per_line)
		{
			points[i][j] = init_point(data, j, i);
			if (!points[i][j])
				return (clear_point(data), NULL);
			points[i][j]->nb_line = data.nb_line;
			points[i][j]->elem_per_line = data.elem_per_line;
			points[i][j]->value = ft_atoi((const char *)*data.line++);
			points[i][j]->rotated_y -= (points[i][j]->value * 2) * data.grid.zoom;
			points[i][j]->color = init_colour(-1, -1, -1, -1);
			j++;
		}
		points[i][j] = NULL;
		i++;
	}
	points[i] = NULL;
	connect_points(points, data);
	return (points);
}

t_point	*init_point(t_data data, int x, int y)
{
	int				beg_x;
	int				beg_y;
	struct s_point	*new;

	new = malloc(sizeof(struct s_point));
	if (!new)
		return (NULL);
 	beg_y = data.grid.grid_height - ((data.grid.wire_len * data.grid.zoom) * (data.nb_line / 2));
	new->tab_y = y;
	new->y = beg_y + ((y + data.grid.y_decal) * (data.grid.wire_len * data.grid.zoom));
	new->rotated_y = new->y;
	
	beg_x = data.grid.grid_width - ((data.grid.wire_len * data.grid.zoom) * (data.elem_per_line / 2));
	new->tab_x = x;
	new->x = beg_x + ((x + data.grid.x_decal) * (data.grid.wire_len * data.grid.zoom));
	new->rotated_x = new->x;
	get_rotated_point(data, &(new->rotated_x), &(new->rotated_y));	
	return (new);
}

void	get_rotated_point(t_data data, int *x, int *y)
{	
	double	radian;
	double	cos_rad;
	double	sin_rad;
	int		temp_x;
	int		temp_y;

	radian = data.grid.radian_x;
	cos_rad = cos(radian);
	sin_rad = sin(radian);
	temp_x = (int)(cos_rad * (*x - data.grid.grid_width)
			- sin_rad * (*y - data.grid.grid_height) + data.grid.grid_width);
	temp_y = (int)(sin_rad * (*x - data.grid.grid_width)
			+ cos_rad * (*y - data.grid.grid_height) + data.grid.grid_height);
	*x = temp_x;
	*y = temp_y;
}

void	set_colour(t_data *data)
{
	int		y;
	int		x;
	double	gradiant;

	y = 0;
	while (data->points[y])
	{
		x = 0;
		while (data->points[y][x])
		{
			if (data->points[y][x]->value == 0)
				data->points[y][x]->color = init_colour(0, ZERO_R, ZERO_G, ZERO_B);
			else if (data->points[y][x]->value == get_highest_altitude(*data))
				data->points[y][x]->color = init_colour(0, HIGHEST_R, HIGHEST_G, HIGHEST_B);
			else if (data->points[y][x]->value == get_lowest_altitude(*data))
				data->points[y][x]->color = init_colour(0, LOWEST_R, LOWEST_G, LOWEST_B);
			else if (data->points[y][x]->value > 0)
			{
				gradiant = (double)data->points[y][x]->value / get_highest_altitude(*data);
				data->points[y][x]->color = init_colour(0,
				BEG_R - (gradiant * get_dif(BEG_R, HIGHEST_R)),
				BEG_G - (gradiant * get_dif(BEG_G, HIGHEST_G)),
				BEG_B - (gradiant * get_dif(BEG_B, HIGHEST_B)));
			}
			x++;
		}
		y++;
	}
	return ;
}

t_colour	init_colour(int colour, int r, int g, int b)
{
	struct s_colour elem;

	elem.r = r;
	elem.g = g;
	elem.b = b;
	elem.colour = (r * 256 * 256) + (g * 256) + b;
	if (r == 0 && g == 0 && b == 0 && colour != 0)
	{
		elem.colour = colour;
		elem.r = (colour >> 16) / 255.0;
		elem.g = (colour >> 8) / 255.0;
		elem.b = colour / 255.0;
	}
	return (elem);
}