/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:55:39 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/12 02:42:35 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point	***parse_points(int fd)
{
	int				i;
	int				j;
	t_parse_data	data;
	t_point			***points;

	data.line = get_parse_data(&data.nb_line, &data.elem_per_line, fd);
	points = malloc((data.nb_line + 1) * sizeof(t_point));
	if (!points)
		return (NULL);
	i = 0;
	while (i < data.nb_line)
	{
		j = 0;
		points[i] = malloc((data.elem_per_line + 1) * sizeof(t_point));
		if (!points[i])
			return (NULL);
		while (j < data.elem_per_line)
		{
			points[i][j] = init_point(i, j,
					ft_atoi((const char *)*data.line++));
			if (!points[i][j])
				return (NULL);
			j++;
		}
		points[i][j] = NULL;
		i++;
	}
	points[i] = NULL;
	connect_points(points, data);
	ft_printf("value at 0:0 : %i\n", points[0][0]->value);
	ft_printf("value below : %i\n", points[0][0]->below_point->value);
	ft_printf("value right : %i\n", points[0][0]->right_point->value);
	return (points);
}

void	connect_points(t_point ***points, t_parse_data data)
{
	int	i;
	int	j;

	i = 0;
	while (points[i])
	{
		j = 0;
		while (points[i][j])
		{
			add_right_point(points, i, j, data);
			add_left_point(points, i, j, data);
			add_above_point(points, i, j);
			add_below_point(points, i, j, data);
			j++;
		}
		i++;
	}
}

void	add_right_point(t_point ***points, int i, int j, t_parse_data data)
{
	if (i > (data.nb_line - 1) || j >= (data.elem_per_line - 1))
		return ;
	points[i][j]->right_point = (points[i][j + 1]);
}

void	add_left_point(t_point ***points, int i, int j, t_parse_data data)
{
	if (i > (data.nb_line - 1) || j == 0)
		return ;
	points[i][j]->left_point = (points[i][j - 1]);
}

void	add_above_point(t_point ***points, int i, int j)
{
	if (i <= 0)
		return ;
	points[i][j]->above_point = (points[i - 1][j]);
}

void	add_below_point(t_point ***points, int i, int j, t_parse_data data)
{
	if (i >= (data.nb_line - 1))
		return ;
	points[i][j]->below_point = (points[i + 1][j]);
}


char	**get_parse_data(int *nb_line, int *len, int fd)
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
		(*nb_line)++;
	}
	elems = ft_split(line, ' ');
	if (elems)
		*len = (get_nb_of_element_in_array(elems)) / *nb_line;
	return (elems);
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

t_point	*init_point(int x, int y, int value)
{
	struct s_point	*new_el;

	new_el = malloc(sizeof(struct s_point));
	if (!new_el)
		return (NULL);
	new_el->x = x;
	new_el->y = y;
	new_el->value = value;
	new_el->left_point = NULL;
	new_el->right_point = NULL;
	new_el->above_point = NULL;
	new_el->below_point = NULL;
	return (new_el);
}
