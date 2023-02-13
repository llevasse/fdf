/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:03:47 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/13 16:04:24 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
