/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 00:47:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/21 01:24:53 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	zoom_in(t_data *data)
{
		reset_img(data);
		clear_point(*data);
		clear_line(*data);
		data->grid.zoom *= 1.5;
		data->points = parse_points(*data);
		data->lines = get_all_lines(*data);
		render(data);
}

void	zoom_out(t_data *data)
{
		reset_img(data);
		clear_point(*data);
		clear_line(*data);
		data->grid.zoom *= 0.5;
		data->points = parse_points(*data);
		data->lines = get_all_lines(*data);
		render(data);		
}

void	reset_img(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (!data->win_ptr)
		return ;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
			img_pix_put(&data->img, x++, y, BG);
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	data->img.mlx_img, 0, 0);
}