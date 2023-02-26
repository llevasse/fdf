/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:35:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/26 13:03:57 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	clear_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	clear_point(t_data data)
{
 	int	x;
	int	y;
	
	y = 0;
	x = 0;
	if (data.points[0][0] == NULL)
	{
		while (x < data.nb_line)
			data.points[x++] -= data.elem_per_line;
	}
	while (data.points[y])
	{
		x = 0;
		while (data.points[y][x])
		{
			free(data.points[y][x]);
			data.points[y][x++] = NULL;
		}
		free(data.points[y][x]);
		free(data.points[y]);
		data.points[y++] = NULL;
	}
	free (data.points[y]);
	free (data.points);
	data.points = NULL;
}

void	clear_line(t_data data)
{
	int	i;

	i = 1;
	if (!(*data.lines))
		data.lines--;
	while ((*data.lines)->line_id != 0 || !(*data.lines))
	{
		data.lines--;
		i++;
	}
	while (*data.lines)
	{
		free(*data.lines);
		*(data.lines)++ = NULL;
	}
	free (*data.lines);
	data.lines -= i;
	free (data.lines);
	data.lines = NULL;
	(void)data;
}

void	free_matrix(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (matrix->matrix[i])
	{
		free(matrix->matrix[i]);
		matrix->matrix[i++] = NULL;
	}
	free(matrix);
	matrix = NULL;
}
