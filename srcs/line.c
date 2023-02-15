/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:46:46 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/15 12:13:14 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_line	**get_all_lines(t_data data)
{
	struct s_line	**line;
	int				i;

	i = 0;
	line = malloc(((data.elem_per_line * data.nb_line) / 2) * sizeof(struct s_line));
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
	line->distance_x = abs(point_a->rotated_x - point_b->rotated_x);
	line->distance_y = abs(point_a->rotated_y - point_b->rotated_y);
	if (abs(line->distance_x) > abs(line->distance_y))
		line->len = abs(line->distance_x);
	else
		line->len = abs(line->distance_y);
	line->x_increment = line->distance_x / line->len;
	line->y_increment = line->distance_y / line->len;
	return (line);
}

void	draw_line(t_data *data, t_line *line, int decide)
{	
	int	pk;
	int	x;
	int	y;
	int	i;

	x = line->x_a;
	y = line->y_a;
	pk = 2 * line->distance_y - line->distance_x;
	i = 0;
	while (i <= line->distance_x)
	{
		if (x < line->x_b)
			x++;
		else
			x--;
		if (pk < 0)
		{
			if (!decide)
				img_pix_put(&data->img, x, y, WHITE);
			else
				img_pix_put(&data->img, y, x, WHITE);
			pk = pk + 2 * line->distance_y;
		}
		else
		{
			if (y < line->y_b)
				y++;
			else
				y--;
			if (!decide)
				img_pix_put(&data->img, x, y, WHITE);
			else
				img_pix_put(&data->img, y, x, WHITE);
			pk = pk + 2 * line->distance_y - 2 * line->distance_x;
		}
		i++;
	}
}
