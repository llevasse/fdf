/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:35:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/15 10:21:55 by llevasse         ###   ########.fr       */
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
	*data.points -= (data.elem_per_line - 1);
	while (*data.points)
	{
		while (**data.points)
		{
			free(**data.points);
			*(*data.points)++ = NULL;
		}
		free (**data.points);
		*data.points -= (data.elem_per_line - 1);
		free (*data.points);
		*(data.points)++ = NULL;
	}
	data.points -= (data.nb_line);
	free (data.points);
	data.points = NULL;
}

void	clear_line(t_data data)
{
	int	i;

	i = 1;
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
