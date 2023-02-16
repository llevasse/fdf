/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:55:39 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/16 18:58:30 by llevasse         ###   ########.fr       */
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
			points[i][j] = init_point(data, i, j);
			if (!points[i][j])
				return (clear_point(data), NULL);
			points[i][j]->nb_line = data.nb_line;
			points[i][j]->elem_per_line = data.elem_per_line;
			points[i][j]->value = ft_atoi((const char *)*data.line++);
			points[i][j]->rotated_y -= points[i][j]->value;
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
 	beg_y = data.grid.grid_height - (data.grid.wire_len * (data.nb_line / 2));
	beg_x = data.grid.grid_width - (data.grid.wire_len * (data.elem_per_line / 2));
	new->tab_x = x;
	new->tab_y = y;
	new->x = beg_x + (x * data.grid.wire_len);
	new->y = beg_y + (y * data.grid.wire_len);
	new->rotated_x = new->x;
	new->rotated_y = new->y;
	get_rotated_point(data, &(new->rotated_x), &(new->rotated_y));	
	return (new);
}

void	get_rotated_point(t_data data, int *x, int *y)
{	
	double	radian;
	double	cos_rad;
	double	sin_rad;

	radian = data.grid.radian_x;
	cos_rad = cos(radian);
	sin_rad = sin(radian);
	*x = (int)((*x * cos_rad) - (*y * sin_rad));
	*y = (int)((*y * cos_rad) + (*x * sin_rad));
}
