/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:46:43 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/28 22:01:09 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_matrix	*multiplie_matrix(t_matrix matrix_a, t_matrix matrix_b)
{
	struct s_matrix	*matrix_c;
	int				rows;
	int				column;
	int				temp;
	int				sum;

	if (matrix_a.nb_rows != matrix_b.nb_column)
		return (NULL);
	matrix_c = init_matrix(matrix_a.nb_rows, matrix_b.nb_column);
	if (!matrix_c)
		return (NULL);
	rows = 0;
	while (rows <= matrix_c->nb_rows)
	{
		column = 0;
		while (column <= matrix_c->nb_column)
		{
			sum = 0;
			temp = 0;
			while (temp <= matrix_c->nb_column)
			{
				sum += matrix_a.matrix[rows][temp]
					* matrix_b.matrix[temp][column];
				temp++;
			}
			matrix_c->matrix[rows][column++] = sum;
		}
		rows++;
	}
	return (matrix_c);
}

t_matrix	*init_matrix(int nb_rows, int nb_column)
{
	struct s_matrix	*matrix;
	int				i;

	i = 0;
	matrix = malloc(sizeof(struct s_matrix));
	if (!matrix)
		return (NULL);
	matrix->nb_column = nb_column;
	matrix->nb_rows = nb_rows;
	matrix->matrix = (int **)malloc((nb_rows) * sizeof(int *));
	if (!matrix->matrix)
		return (free_matrix(matrix), NULL);
	matrix->matrix[nb_rows] = NULL;
	while (i < nb_rows)
	{
		matrix->matrix[i] = (int *)malloc((nb_column) * sizeof(int));
		if (!matrix->matrix[i])
			return (free_matrix(matrix), NULL);
	}
	return (matrix);
}

