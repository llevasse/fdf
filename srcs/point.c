/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:55:39 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/15 11:24:44 by llevasse         ###   ########.fr       */
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
		while (j < (data.elem_per_line - 1))
		{
			points[i][j] = init_point(i, j,
					ft_atoi((const char *)*data.line++), data);
			if (!points[i][j])
				return (clear_point(data), NULL);
			points[i][j]->nb_line = data.nb_line;
			points[i][j]->elem_per_line = data.elem_per_line;
			j++;
		}
		points[i][j] = NULL;
		i++;
	}
	points[i] = NULL;
	clear_split(data.line - (i * j));
	connect_points(points, data);
	return (points);
}

char	**get_data(int *nb_line, int *len, int fd)
{
	char	*line;
	char	*temp;
	char	**elems;

	line = get_next_line(fd);
	*nb_line = 0;
	while (line)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		line = ft_strjoin(line, temp);
		free(temp);
		(*nb_line)++;
	}
	elems = ft_split(line, " \n");
	if (elems)
		*len = (get_nb_of_element_in_array(elems)) / *nb_line;
	return (free(line), elems);
}

int	get_nb_of_element_in_array(char **str)
{
	int		i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

t_point	*init_point(int x, int y, int value, t_data data)
{
	int				begining_x;
	int				begining_y;
	double			cos_angle;
	double			sin_angle;
	struct s_point	*new_el;
	new_el = malloc(sizeof(struct s_point));
	if (!new_el)
		return (NULL);
	begining_x = data.grid.grid_width - (data.grid.wire_len * (data.nb_line / 2));
	begining_y = data.grid.grid_height - (data.grid.wire_len * (data.elem_per_line / 2));
	new_el->tab_x = x;
	new_el->tab_y = y;
	new_el->x = (begining_x) + (x * data.grid.wire_len);
	new_el->y = (begining_y) + (y * data.grid.wire_len);
	cos_angle = cos(data.grid.x_angle);
	sin_angle = sin(data.grid.x_angle);
	new_el->rotated_x = (int)((new_el->x) * cos_angle) - ((new_el->y) * sin_angle);
	new_el->rotated_y = (int)((new_el->x) * sin_angle) + ((new_el->y) * cos_angle);
	new_el->value = value;
	new_el->color = WHITE;
	new_el->left_point = NULL;
	new_el->right_point = NULL;
	new_el->above_point = NULL;
	new_el->below_point = NULL;
	return (new_el);
}
