/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:55:30 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/14 20:18:56 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	handle_no_event(void *data)
{
	(void)data;
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		clear_point(data->points, data->parsed_data);
		clear_line(data->lines, data->parsed_data);
	}
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	render(t_data *data)
{
	if (!data->win_ptr)
		return (1);
	while (*data->lines)
	{
		draw_line(data, *data->lines);
		data->lines++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	t_parse_data	parsed_data;
	int				fd;

	if (argc == 1)
		return (1);
	fd = open(argv[1], O_RDONLY);
	parsed_data.line = get_parse_data(&parsed_data.nb_line, &parsed_data.elem_per_line, fd);
	data.parsed_data = parsed_data;
	data.points = parse_points(parsed_data);
	data.lines = get_all_lines(data.points, parsed_data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"fdf");
	if (!data.win_ptr)
		return (free(data.win_ptr), 1);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_key_hook(data.win_ptr, &handle_input, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	(void)data.points;
	(void)fd;
}
