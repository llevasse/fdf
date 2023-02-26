/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:55:39 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/26 10:10:39 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point	***parse_points(t_data data)
{
	int		i;
	int		j;
	t_point	***points;

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
			points[i][j] = init_point(data, j, i,
					(ft_atoi((const char *)*data.line)));
			if (!points[i][j])
				return (clear_point(data), NULL);
			points[i][j]->color = init_colour(-1, -1, -1, -1);
			if (ft_is_in_str((const char *)*data.line++, ','))
				points[i][j]->color = init_colour_from_str((const char *)*(data.line
							- 1));
			points[i][j]->nb_line = data.nb_line;
			points[i][j]->elem_per_line = data.elem_per_line;
			/* 			points[i][j]->rotated_y -= (points[i][j]->value
								* data.grid.wire_len)
				* data.grid.zoom;
 */
			j++;
		}
		points[i][j] = NULL;
		i++;
	}
	points[i] = NULL;
	connect_points(points, data);
	return (points);
}

t_point	*init_point(t_data data, int x, int y, int z)
{
	int				beg_x;
	int				beg_y;
	struct s_point	*new;

	new = malloc(sizeof(struct s_point));
	if (!new)
		return (NULL);
	beg_y = data.grid.grid_height - ((data.grid.wire_len * data.grid.zoom)
			* (data.nb_line / 2));
	new->tab_y = y;
	new->y = beg_y + (y * (data.grid.wire_len * data.grid.zoom))
		+ data.grid.y_decal;
	new->rotated_y = new->y;
	beg_x = data.grid.grid_width - ((data.grid.wire_len * data.grid.zoom)
			* (data.elem_per_line / 2));
	new->tab_x = x;
	new->x = beg_x + (x * (data.grid.wire_len * data.grid.zoom))
		+ data.grid.x_decal;
	new->rotated_x = new->x;
	new->value = z;
	get_rotated_point(data, &(new->rotated_x), &(new->rotated_y), (z
				* data.grid.zoom));
	return (new);
}

double	get_iso_radian(int angle, int minus)
{
	int	iso_angle;

	if (minus == 0)
	{
		iso_angle = angle + 120;
		if (iso_angle < 0)
			iso_angle += 360;
		while (iso_angle > 360)
			iso_angle -= 360;
		return (((double)iso_angle * PI) / 180);
	}
	iso_angle = angle - 120;
	if (iso_angle < 0)
		iso_angle += 360;
	while (iso_angle > 360)
		iso_angle -= 360;
	return (((double)iso_angle * PI) / 180);
}

void	get_rotated_point(t_data data, int *x, int *y, int z)
{
	double	radian;
	double	cos_rad;
	double	sin_rad;
	int		temp_x;
	int		temp_y;

	radian = data.grid.radian_x;
	cos_rad = cos(radian);
	sin_rad = sin(radian);
	temp_x = (int)(*x * cos_rad) + ((double)*y
			* cos(get_iso_radian(data.grid.x_angle, 0))) + ((double)z
			* cos(get_iso_radian(data.grid.x_angle, 1)));
	temp_y = (int)((double)*x * sin_rad) + ((double)*y
			* sin(get_iso_radian(data.grid.x_angle, 0))) + ((double)z
			* sin(get_iso_radian(data.grid.x_angle, 1)));

	*x = temp_x;
	*y = temp_y;
	(void)z;
}

t_colour	init_colour_from_str(const char *str)
{
	int	r;
	int	g;
	int	b;

	r = 1;
	g = 1;
	b = 1;
	while (*str != 'x')
		str++;
	str++;
	if (ft_strlen(str) >= 2)
	{
		r *= hex2int(*str++) + 1;
		if (hex2int(*str++) != 0)
			r *= hex2int(*(str - 1)) + 1;
		r--;
	}
	if (ft_strlen(str) >= 2)
	{
		g *= hex2int(*str++) + 1;
		if (hex2int(*str++) != 0)
			g *= hex2int(*(str - 1)) + 1;
		g--;
	}
	if (ft_strlen(str) >= 2)
	{
		b *= hex2int(*str++) + 1;
		if (hex2int(*str++) != 0)
			b *= hex2int(*(str - 1)) + 1;
		b--;
	}
	return (init_colour(0, r, g, b));
}

int	hex2int(char byte)
{
	if (byte >= '0' && byte <= '9')
		byte = byte - '0';
	else if (byte >= 'a' && byte <= 'f')
		byte = byte - 'a' + 10;
	else if (byte >= 'A' && byte <= 'F')
		byte = byte - 'A' + 10;
	return ((int)byte);
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
		while (data->points[y][x] && data->points[y][x]->color.colour != -1)
			x++;
		while (data->points[y][x])
		{
			if (data->points[y][x]->value == 0)
				data->points[y][x]->color = init_colour(0, ZERO_R, ZERO_G,
						ZERO_B);
			else if ((data->points[y][x]->value)
					* 2 == get_highest_altitude(*data))
				data->points[y][x]->color = init_colour(0, HIGHEST_R, HIGHEST_G,
						HIGHEST_B);
			else if ((data->points[y][x]->value)
					* 2 == get_lowest_altitude(*data))
				data->points[y][x]->color = init_colour(0, LOWEST_R, LOWEST_G,
						LOWEST_B);
			else if (data->points[y][x]->value > 0)
			{
				gradiant = ((double)data->points[y][x]->value) * 2
					/ get_highest_altitude(*data);
				data->points[y][x]->color = init_colour(0,
														BEG_R - (gradiant
																* get_dif(BEG_R,
																	HIGHEST_R)),
														BEG_G - (gradiant
																* get_dif(BEG_G,
																	HIGHEST_G)),
														BEG_B - (gradiant
																* get_dif(BEG_B,
																	HIGHEST_B)));
			}
			else if (data->points[y][x]->value < 0)
			{
				gradiant = ((double)data->points[y][x]->value) * 2
					/ get_highest_altitude(*data);
				data->points[y][x]->color = init_colour(0,
														BEG_R + (gradiant
																* get_dif(BEG_R,
																	LOWEST_R)),
														BEG_G + (gradiant
																* get_dif(BEG_G,
																	LOWEST_G)),
														BEG_B + (gradiant
																* get_dif(BEG_B,
																	LOWEST_B)));
			}
			x++;
		}
		y++;
	}
	return ;
}

t_colour	init_colour(int colour, int r, int g, int b)
{
	struct s_colour	elem;

	elem.r = r;
	elem.g = g;
	elem.b = b;
	elem.colour = (r * 256 * 256) + (g * 256) + b;
	if (colour == -1)
		elem.colour = -1;
	if (r == 0 && g == 0 && b == 0 && colour != 0)
	{
		elem.colour = colour;
		elem.r = (colour >> 16);
		elem.g = (colour >> 8);
		elem.b = colour;
		if (elem.r < 0)
			elem.r = 0;
		if (elem.r > 255)
			elem.r = 255;
		if (elem.g < 0)
			elem.g = 0;
		if (elem.g > 255)
			elem.g = 255;
		if (elem.b < 0)
			elem.b = 0;
		if (elem.b > 255)
			elem.b = 255;
	}
	return (elem);
}
