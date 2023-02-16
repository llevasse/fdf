/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:22:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/16 18:57:50 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

char	**get_data(int *nb_line, int *len, int fd)
{
	char	*line;
	char	*temp;
	char	**elems;

	line = get_next_line(fd);
	*nb_line = 1;
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
