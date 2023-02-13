/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:35:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/13 18:12:52 by llevasse         ###   ########.fr       */
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

void	clear_point(t_point ***points)
{
	int	i;
	int	j;

	i = 0;
	while (points[i])
	{
		j = 0;
		while (points[i][j])
		{
			free(points[i][j]);
			points[i][j++] = NULL;
		}
		free (points[i]);
		points[i++] = NULL;
	}
	free(points);
	points = NULL;
}

void	clear_line(t_line **line)
{
	while (*line)
	{
		free(*line);
		line = NULL;
	}
	free(line);
	line = NULL;
}