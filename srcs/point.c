/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:55:39 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/16 15:00:00 by llevasse         ###   ########.fr       */
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
		if (i == 0 && j == 0)
			points[i][j] = init_initial_point(i, j, data);
		if (i > 0)
			points[i][j] = init_right_point(data, points[i - 1][j], i, j);
		if (!points[i][j++])
			return (clear_point(data), NULL);
		while (j < (data.elem_per_line - 1))
		{
			points[i][j] = init_right_point(data, points[i][j - 1], i, j);
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

t_point *init_right_point(t_data data, t_point *left_point, int x, int y)
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
	new->x = (beg_x) + (x * data.grid.wire_len);
	new->y = (beg_y) + (y * data.grid.wire_len);
	new->rotated_x = new->x;
	new->rotated_y = new->y;
	get_rotated_point(data, left_point, &(new->rotated_x), &(new->rotated_y));
	return (new);
}

t_point	*init_initial_point(int x, int y, t_data data)
{
	int				begining_x;
	int				begining_y;
	struct s_point	*new_el;

	new_el = malloc(sizeof(struct s_point));
	if (!new_el)
		return (NULL);
	new_el->color = WHITE;
	
	begining_x = data.grid.grid_width - (data.grid.wire_len * (data.elem_per_line / 2));
	begining_y = data.grid.grid_height - (data.grid.wire_len * (data.nb_line / 2));
	new_el->tab_x = x;
	new_el->tab_y = y;
	new_el->x = begining_x;
	new_el->y = begining_y;
	new_el->rotated_x = begining_x;
	new_el->rotated_y = begining_y;

	return (new_el);
}

void	get_rotated_point(t_data data, t_point *point, int *x, int *y)
{
	double	radian;

	radian = data.grid.radian_x;
	*x = (int)(cos(radian) * (*x - point->rotated_x) - sin(radian) * (*y - point->rotated_y) + point->rotated_x);
	*y = (int)(sin(radian) * (*x - point->rotated_x) + cos(radian) * (*y - point->rotated_y) + point->rotated_y);
}
