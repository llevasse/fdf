/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:46:46 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/13 18:14:06 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_line	**get_all_lines(t_point ***points, t_parse_data data)
{
	struct s_line	**line;
	int				i;

	i = 0;
	line = malloc(((data.elem_per_line * data.nb_line) / 2) * sizeof(struct s_line));
	while (points)
	{
		while (*points)
		{
			line[i++] = init_line(**points, (**points)->right_point);
			if (!line[i - 1])
				return (clear_line(line), NULL);
			line[i++] = init_line(**points, (**points)->below_point);
			if (!line[i - 1])
				return (clear_line(line), NULL);
			(*points)++;
		}
		points++;
	}
	line[i] = NULL;
	return (line);
}

t_line	*init_line(t_point *point_a, t_point *point_b)
{
	struct s_line	*line;

	line = malloc(sizeof(struct s_line));
	line->xA = point_a->x;
	line->yA = point_a->y;
	line->xB = point_b->x;
	line->yB = point_b->y;
	line->distance_x = point_a->x - point_b->x;
	line->distance_y = point_a->y - point_b->y;
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
	while (line->xA < line->xB)
	{
		img_pix_put(&data->img, line->xA, line->xB, WHITE);
		line->xA += line->x_increment;
		line->yA += line->y_increment;
	}
}
