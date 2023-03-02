/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:55:30 by llevasse          #+#    #+#             */
/*   Updated: 2023/03/02 10:47:47 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	handle_no_event(void *data)
{
	(void)data;
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img_isometric.mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->img_conic.mlx_img);
	data->win_ptr = NULL;
	clear_point(*data);
	clear_line(*data);
	clear_split(data->line);
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_window(data);
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
	if (keysym == XK_p || keysym == XK_P)
		print_grid_info(data);
	if ((keysym == XK_c || keysym == XK_C))
		render_conic(data);
	if ((keysym == XK_i || keysym == XK_I))
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img_isometric.mlx_img, 0, 0);
		data->current_img = &data->img_isometric;
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

void	print_grid_info(t_data *data)
{
	ft_printf("grid of size %ix", data->grid.grid_width);
	ft_printf("%i\n", data->grid.grid_height);
	ft_printf("moved by x of %i ", data->grid.x_decal);
	ft_printf("and by y of %i ", data->grid.y_decal);
	ft_printf("with a rotation of %i\n", data->grid.angle);
	print_point_info(data);
}
void	print_point_info(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (data->points_conic[0][0] == NULL)
	{
		while (y < data->nb_line)
			data->points_conic[y++] -= data->elem_per_line;
	}
	y = 0;
	while (data->points_conic[y])
	{
		x = 0;
		ft_printf("| ");
		while (data->points_conic[y][x])
		{
			ft_printf("{%i.%i.%i} | ", data->points_conic[y][x]->rotated_x,
					data->points_conic[y][x]->rotated_y,
					data->points_conic[y][x]->value);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

int	render(t_data *data)
{
	if (!data->win_ptr)
		return (1);
	while (*data->lines)
	{
		draw_line(data, *data->lines, &data->img_isometric);
		data->lines++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->current_img->mlx_img, 0, 0);
	return (0);
}

t_data	init_data(int fd)
{
	t_data	data;

	data.grid = init_grid();
	data.line = get_data(&data.nb_line, &data.elem_per_line, fd);
	data.points = parse_points(data);
	data.points_conic = parse_point_conic(data);
	set_colour_iso(&data);
	set_colour_conic(&data);
	data.beg_colour = init_colour(0, BEG_R, BEG_G, BEG_B);
	data.zero_colour = init_colour(0, ZERO_R, ZERO_G, ZERO_B);
	data.lines_conic = get_all_conic_lines(data);
	data.lines = get_all_lines(data);
	data.highest_altitude = get_highest_altitude(data);
	data.lowest_altitude = get_lowest_altitude(data);
	data.mlx_ptr = mlx_init();
	return (data);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		fd;

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
	data.img_isometric.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	data.img_isometric.addr = mlx_get_data_addr(data.img_isometric.mlx_img,
												&data.img_isometric.bpp,
												&data.img_isometric.line_len,
												&data.img_isometric.endian);
	data.img_conic.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	data.img_conic.addr = mlx_get_data_addr(data.img_conic.mlx_img,
											&data.img_conic.bpp,
											&data.img_conic.line_len,
											&data.img_conic.endian);
	data.current_img = &data.img_isometric;
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_input, &data);
	mlx_hook(data.win_ptr, 17, 0, &close_window, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	(void)data.points;
	(void)fd;
}
