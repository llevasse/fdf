/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:46:46 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/16 15:56:16 by llevasse         ###   ########.fr       */
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
	return (line);
}

void	draw_line(t_data *data, t_line *line)
{	
	int	pk;
	int	x;
	int	y;
	int	i;
	int	color;

	x = line->x_a;
	y = line->y_a;
	color = WHITE;
	pk = 2 * line->distance_y - line->distance_x;
	i = 0;
	while (i <= line->distance_x || i <= line->distance_y)
	{
		if (x < line->x_b)
			x++;
		else
			x--;
		if (x >= WINDOW_WIDTH)
			break ;
		if (pk < 0)
		{
			img_pix_put(&data->img, x, y, color);
			pk = pk + 2 * line->distance_y;
		}
		else
		{
			if (y < line->y_b)
				y++;
			else
				y--;
			if (y >= WINDOW_HEIGHT)
				break ;
			img_pix_put(&data->img, x, y, color);
			pk = pk + 2 * line->distance_y - 2 * line->distance_x;
		}
		i++;
	}
}
