/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:35:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/14 21:06:54 by llevasse         ###   ########.fr       */
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

void	clear_point(t_point ***points, t_parse_data data)
{
	*points -= (data.elem_per_line - 1);
	while (*points)
	{
		while (**points)
		{
			free(**points);
			*(*points)++ = NULL;
		}
		free (**points);
		*points -= (data.elem_per_line - 1);
		free (*points);
		*(points)++ = NULL;
	}
	points -= (data.nb_line);
	free (points);
	points = NULL;
}

void	clear_line(t_line **line, t_parse_data data)
{
	int	i;

	i = 1;
	line--;
	while ((*line)->line_id != 0 || !(*line))
	{
		line--;
		i++;
	}
	while (*line)
	{
		free(*line);
		*(line)++ = NULL;
	}
	free (*line);
	line -= i;
	free (line);
	line = NULL;
	(void)data;
}
