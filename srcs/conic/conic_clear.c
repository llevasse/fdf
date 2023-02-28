/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 22:52:25 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/28 22:55:20 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clear_conic_point(t_data data)
{
	int	x;
	int	y;

	y = 0;
	reset_ptr_point(data);
	while (data.points_conic[y])
	{
		x = 0;
		while (data.points_conic[y][x])
		{
			free(data.points_conic[y][x]);
			data.points_conic[y][x++] = NULL;
		}
		free(data.points_conic[y][x]);
		free(data.points_conic[y]);
		data.points_conic[y++] = NULL;
	}
	free(data.points_conic[y]);
	free(data.points_conic);
	data.points_conic = NULL;
}

static void	clear_conic_line(t_data data)
{
	int i;

	i = 1;
	if (!(*data.lines_conic))
		data.lines_conic--;
	while ((*data.lines_conic)->line_id != 0 || !(*data.lines_conic))
	{
		data.lines_conic--;
		i++;
	}
	while (*data.lines_conic)
	{
		free(*data.lines_conic);
		*(data.lines_conic)++ = NULL;
	}
	free(*data.lines_conic);
	data.lines_conic -= i;
	free(data.lines_conic);
	data.lines_conic = NULL;
	(void)data;
}