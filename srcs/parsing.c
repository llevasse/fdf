/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:55:39 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/12 01:13:48 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point	***parse_points(int fd)
{
	int		i;
	int		j;
	char	**line;
	int		nb_line;
	int		len;
	t_point	***points;

	line = get_parse_data(&nb_line, &len, fd);
	points = malloc(nb_line * sizeof(t_point));
	if (!points)
		return (NULL);
	ft_printf("nb_line : %i\nnb_elem per line : %i\n", nb_line, len);
	i = 0;
	while (i < nb_line)
	{
		j = 0;
		points[i] = malloc(len * sizeof(t_point));
		while (j < len)
		{
			points[i][j] = init_point(i, j, ft_atoi((const char *)*line++));
			j++;
		}		
		i++;
	}

	return (points);
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

	new_el = malloc(sizeof(struct s_list));
	if (!new_el)
		return (NULL);
	new_el->x = x;
	new_el->y = y;
	new_el->value = value;
	return (new_el);
}
