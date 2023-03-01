/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 23:36:34 by llevasse          #+#    #+#             */
/*   Updated: 2023/03/01 18:25:36 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

t_line	**get_all_conic_lines(t_data data)
{
	struct s_line	**line;
	int				i;

	i = 0;
	line = malloc(((data.elem_per_line * data.nb_line))
			* sizeof(struct s_line));
	while (*data.points_conic)
	{
		while (**data.points_conic)
		{
			if ((**data.points_conic)->right_point && **data.points_conic)
			{
				line[i] = init_line(**data.points_conic, (**data.points_conic)->right_point,
						i);
				if (!line[i++])
					return (clear_line(data), NULL);
			}
			if ((**data.points_conic)->below_point && **data.points_conic)
			{
				line[i] = init_line(**data.points_conic, (**data.points_conic)->below_point,
						i);
				if (!line[i++])
					return (clear_line(data), NULL);
			}
			(*data.points_conic)++;
		}
		data.points_conic++;
	}
	line[i] = NULL;
	return (line);
}


