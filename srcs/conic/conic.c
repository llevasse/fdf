/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 22:21:36 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/28 23:46:07 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	render_conic(t_data *data)
{
	ft_printf("switch to conic view\n");
	if (!data->win_ptr)
		return (1);
	while (*data->lines_conic)
	{
		draw_line(data, *data->lines_conic, &data->img_conic);
		data->lines_conic++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_conic.mlx_img, 0,
			0);
	return (0);
}
