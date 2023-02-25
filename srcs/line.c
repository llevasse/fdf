/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:46:46 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/25 19:03:37 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_line	**get_all_lines(t_data data)
{
	struct s_line	**line;
	int				i;

	i = 0;
	line = malloc(((data.elem_per_line * data.nb_line)) * sizeof(struct s_line));
	while (*data.points)
	{
		while (**data.points)
		{
			if ((**data.points)->right_point && **data.points)
			{
				line[i] = init_line(**data.points, (**data.points)->right_point, i);
				if (!line[i++])
					return (clear_line(data), NULL);
			}
			if ((**data.points)->below_point && **data.points)
			{
				line[i] = init_line(**data.points, (**data.points)->below_point, i);
				if (!line[i++])
					return (clear_line(data), NULL);
			}
			(*data.points)++;
		}
		data.points++;
	}
	line[i] = NULL;
	return (line);
}

t_line	*init_line(t_point *point_a, t_point *point_b, int line_id)
{
	struct s_line	*line;

	line = malloc(sizeof(struct s_line));
	line->x_a = point_a->rotated_x;
	line->y_a = point_a->rotated_y;
	line->x_b = point_b->rotated_x;
	line->y_b = point_b->rotated_y;
	line->line_id = line_id;
	line->distance_x = abs(point_b->rotated_x - point_a->rotated_x);
	line->distance_y = abs(point_b->rotated_y - point_a->rotated_y);
	line->len = (int)sqrt(pow(line->distance_y, 2) + pow(line->distance_x, 2));
	line->altitude_a = point_a->value;
	line->altitude_b = point_b->value;
	line->colour_a = point_a->color;
	line->colour_b = point_b->color;
	if (line->altitude_a != 0 || line->altitude_b != 0)
	{
		if (line->altitude_a == 0 && line->altitude_b != 0)
			line->colour_a = init_colour(0, BEG_R, BEG_G, BEG_B);
		if (line->altitude_b == 0 && line->altitude_a != 0)
			line->colour_b = init_colour(0, BEG_R, BEG_G, BEG_B);
	}
 	if (line->altitude_a || line->altitude_b)
		line->z_ratio = get_z_ratio(line); // try to get the ratio of altitude increase for color gradiant
	return (line);
}

int	get_z_ratio(t_line *line)
{
	if (line->altitude_a == line->altitude_b)
		return (0);
	if (line->altitude_a > line->altitude_b)
		return (-1);
	return (1);
}

void	draw_line(t_data *data, t_line *line)
{	
	int	x;
	int	y;
	int	i;
	int	err;
	int	e2;
	int	incr_x;
	int	incr_y;

	x = line->x_a;
	y = line->y_a;
	if (x < line->x_b)
		incr_x = 1;
	else
		incr_x = -1;
	if (y < line->y_b)
		incr_y = 1;
	else
		incr_y = -1;
	if (line->distance_x > line->distance_y)
		err = line->distance_x / 2;
	else
		err = (0 - line->distance_y) / 2;
	i = 0;
	while (i <= line->distance_x || i <= line->distance_y)
	{
		if (y >= 0 && y <= WINDOW_HEIGHT && x >= 0 && x <= WINDOW_WIDTH)
			img_pix_put(&data->img, x, y, get_colour(*line, i, *data));
		e2 = err;
		if (e2 > (0 - line->distance_x))
		{
			err -= line->distance_y;
			x += incr_x;
		}
		if (e2 < line->distance_y)
		{
			err += line->distance_x;
			y += incr_y;
		}
		i++;
	}
}
