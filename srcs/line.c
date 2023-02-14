/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:46:46 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/14 21:01:37 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_line	**get_all_lines(t_point ***points, t_parse_data data)
{
	struct s_line	**line;
	int				i;

	i = 0;
	line = malloc(((data.elem_per_line * data.nb_line) / 2) * sizeof(struct s_line));
	while (*points)
	{
		while (**points)
		{
			if ((**points)->right_point && **points)
			{
				line[i] = init_line(**points, (**points)->right_point, i);
				if (!line[i++])
					return (clear_line(line, data), NULL);
			}
			if ((**points)->below_point && **points)
			{
				line[i] = init_line(**points, (**points)->below_point, i);
				if (!line[i++])
					return (clear_line(line, data), NULL);
			}
			(*points)++;
		}
		points++;
	}
	line[i] = NULL;
	return (line);
}

t_line	*init_line(t_point *point_a, t_point *point_b, int line_id)
{
	struct s_line	*line;

	line = malloc(sizeof(struct s_line));
	line->x_a = point_a->x;
	line->y_a = point_a->y;
	line->x_b = point_b->x;
	line->y_b = point_b->y;
	line->line_id = line_id;
	line->distance_x = abs(point_a->x - point_b->x);
	line->distance_y = abs(point_a->y - point_b->y);
	if (abs(line->distance_x) > abs(line->distance_y))
		line->len = abs(line->distance_x);
	else
		line->len = abs(line->distance_y);
	line->x_increment = line->distance_x / line->len;
	line->y_increment = line->distance_y / line->len;
	return (line);
}

void	draw_line(t_data *data, t_line *line)
{	
	int	x;
	int	y;

	x = line->x_a;
	y = line->y_a;
	while (x < line->x_b || y < line->y_b)
	{
		img_pix_put(&data->img, x, y, WHITE);
		x += line->x_increment;
		y += line->y_increment;
	}
}
