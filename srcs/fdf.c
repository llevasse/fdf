/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:55:30 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/27 12:06:48 by llevasse         ###   ########.fr       */
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
		clear_point(*data);
		clear_line(*data);
		clear_split(data->line);
	}
	if (keysym == XK_KP_Add)
		zoom_in(data);
	if (keysym == XK_KP_Subtract)
		zoom_out(data);
	if (keysym == XK_Left || keysym == XK_KP_Left)
		rotate_left(data, 1);
	if (keysym == XK_Right || keysym == XK_KP_Right)
		rotate_right(data, 1);
	if (keysym == XK_a || keysym == XK_A)
		move_left(data, 30);
	if (keysym == XK_d || keysym == XK_D)
		move_right(data, 30);
	if (keysym == XK_w || keysym == XK_W)
		move_up(data, 30);
	if (keysym == XK_s || keysym == XK_S)
		move_down(data, 30);
	if (keysym == XK_r || keysym == XK_R)
		reset_grid(data);
	print_grid_info(data);
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

void	print_grid_info(t_data *data)
{
	ft_printf("grid of size %ix%i\n\
move by x of %i and by y of %i \
with a rotation of %i\n",
	data->grid.grid_width, data->grid.grid_height, 
	data->grid.x_decal, data->grid.y_decal,
	data->grid.angle);	
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

t_data	init_data(int fd)
{
	t_data data;
	
	data.grid = init_grid();
	data.line = get_data(&data.nb_line, &data.elem_per_line, fd);
	data.points = parse_points(data);
	set_colour(&data);
	data.beg_colour = init_colour(0, BEG_R, BEG_G, BEG_B);
	data.zero_colour = init_colour(0, ZERO_R, ZERO_G, ZERO_B);
	data.lines = get_all_lines(data);
	data.highest_altitude = get_highest_altitude(data);
	data.lowest_altitude = get_lowest_altitude(data);
	data.mlx_ptr = mlx_init();
	
	return (data);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	int				fd;

	if (argc == 1)
		return (1);
	fd = open(argv[1], O_RDONLY);
	data = init_data(fd);
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
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask,  &handle_input, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	(void)data.points;
	(void)fd;
}
