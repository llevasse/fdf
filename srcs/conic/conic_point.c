/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 22:46:54 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/28 23:31:37 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	***parse_point_conic(t_data data)
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
static t_point	*init_point_conic(t_data data, int x, int y, int z)
{
	int				beg_x;
	int				beg_y;
	struct s_point	*new;

	new = malloc(sizeof(struct s_point));
	if (!new)
		return (NULL);
	new->tab_y = y;
	new->tab_x = x;
	beg_x = data.grid.grid_width;
	beg_y = 0;
	new->x = beg_x + (x * data.grid.wire_len);
	new->y = 0;
	if (x != 0)
		rotate_point_conic(data, &(new->rotated_x), &(new->rotated_y), 180
				* ((double)x / (data.elem_per_line - 1)));
	new->value = z * data.grid.z_amplifier;
	return (new);	
}

static void	rotate_point_conic(t_data data, int *x, int *y, int angle)
{
	int temp_x;
	int temp_y;
	int radian;

	radian = (angle * PI) / 180;

	temp_x = cos(radian) * (*x - data.grid.grid_width) - sin(radian) * (*y - 0)
		+ data.grid.grid_width;
	temp_y = sin(radian) * (*x - data.grid.grid_width) + cos(radian) * (*y - 0)
		+ 0;
	*x = temp_x;
	*y = temp_y;
}