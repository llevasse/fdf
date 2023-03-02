/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 22:46:54 by llevasse          #+#    #+#             */
/*   Updated: 2023/03/02 10:36:01 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

t_point	***parse_point_conic(t_data data)
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
			return (clear_conic_point(data), NULL);
		while (j < data.elem_per_line)
		{
			points[i][j] = init_point_conic(data, j, i,
					ft_atoi((const char *)*data.line));
			if (!points[i][j])
				return (clear_conic_point(data), NULL);
			points[i][j]->color = init_colour(-1, -1, -1, -1);
			if (ft_is_in_str((const char *)*data.line++, ','))
				points[i][j]->color = init_colour_from_str((const char *)*(data.line
							- 1));
			points[i][j]->nb_line = data.nb_line;
			points[i][j]->elem_per_line = data.elem_per_line;
			j++;
		}
		points[i++][j] = NULL;
	}
	points[i] = NULL;
	return (connect_points(points, data), points);
}
t_point	*init_point_conic(t_data data, int x, int y, int z)
{
	int				beg_x;
	struct s_point	*new;

	new = malloc(sizeof(struct s_point));
	if (!new)
		return (NULL);
	new->tab_y = y;
	new->tab_x = x;
	beg_x = data.grid.grid_width;
	new->x = beg_x + ((x + y) + (data.grid.wire_len * y));
	new->y = 0;
	new->rotated_x = new->x;
	new->rotated_y = new->y;
	if (x != 0 || y != 0)
		rotate_point_conic(data, &(new->rotated_x), &(new->rotated_y), 180 - (180
				* ((double)x / (data.elem_per_line - 1))));
	new->value = z *data.grid.z_amplifier;
	return (new);
}

void	rotate_point_conic(t_data data, int *x, int *y, int angle)
{
	int		temp_x;
	int		temp_y;
	double	radian;

	radian = ((double)(angle)*PI) / 180;
	temp_x = (int)(cos(radian) * (*x - data.grid.grid_width) - sin(radian)
			* *y);
	temp_y = (int)(sin(radian) * (*x - data.grid.grid_width) + cos(radian)
			* *y);
	*x = temp_x + data.grid.grid_width;
	*y = temp_y;
	(void)data;
}

void	set_colour_conic(t_data *data)
{
	int y;
	int x;
	double gradiant;

	y = 0;
	while (data->points_conic[y])
	{
		x = 0;
		while (data->points_conic[y][x] && data->points_conic[y][x]->color.colour != -1)
			x++;
		while (data->points_conic[y][x])
		{
			if (data->points_conic[y][x]->value == 0)
				data->points_conic[y][x]->color = init_colour(0, ZERO_R, ZERO_G,
						ZERO_B);
			else if ((data->points_conic[y][x]->value)
					* 2 == get_highest_altitude(*data))
				data->points_conic[y][x]->color = init_colour(0, HIGHEST_R, HIGHEST_G,
						HIGHEST_B);
			else if ((data->points_conic[y][x]->value)
					* 2 == get_lowest_altitude(*data))
				data->points_conic[y][x]->color = init_colour(0, LOWEST_R, LOWEST_G,
						LOWEST_B);
			else if (data->points_conic[y][x]->value > 0)
			{
				gradiant = ((double)data->points_conic[y][x]->value) * 2
					/ get_highest_altitude(*data);
				data->points_conic[y][x]->color = init_colour(0,
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
			else if (data->points_conic[y][x]->value < 0)
			{
				gradiant = ((double)data->points_conic[y][x]->value) * 2
					/ get_highest_altitude(*data);
				data->points_conic[y][x]->color = init_colour(0,
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
