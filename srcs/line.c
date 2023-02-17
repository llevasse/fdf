/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:46:46 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/17 23:17:45 by llevasse         ###   ########.fr       */
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
	int				r;
	int				g;
	int				b;
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
	line->incr_r_pace = 0;
	line->incr_r_step = 0;
	line->incr_g_pace = 0;
	line->incr_g_step = 0;
	line->incr_b_pace = 0;
	line->incr_b_step = 0;
	line->altitude_a = point_a->value;
	line->altitude_b = point_b->value;
	r = HIGHEST_COLOR_R;
	g = HIGHEST_COLOR_G;
	b = HIGHEST_COLOR_B;
	if (r == 0)
		r = 1;
	if (g == 0)
		g = 1;
	if (b == 0)
		b = 1;
	line->incr_r_pace = line->len / r; 
	line->incr_r_step = line->incr_r_pace / line->len;
	line->incr_g_pace = line->len / g; 
	line->incr_g_step = line->incr_g_pace / line->len;
	line->incr_b_pace = line->len / b;
	line->incr_b_step = line->incr_b_pace / line->len;
	return (line);
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
			img_pix_put(&data->img, x, y, get_rgb(*line, y, data->highest_altitude));
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
