/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 22:21:36 by llevasse          #+#    #+#             */
/*   Updated: 2023/03/01 19:18:31 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	render_conic(t_data *data)
{
	int	i;

	reset_img(data);
	ft_printf("switch to conic view\n");
	if (!data->win_ptr)
		return (1);
	i = 0;
	if (!(*data->lines_conic))
		data->lines_conic--;
	while ((*data->lines_conic)->line_id != 0 || !(*data->lines_conic))
		data->lines_conic--;
	while (*data->lines_conic)
	{
		draw_line(data, *data->lines_conic, &data->img_conic);
		data->lines_conic++;
		ft_printf("line %i\n", i++);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img_conic.mlx_img, 0, 0);
	data->current_img = &data->img_conic;
	return (0);
}
