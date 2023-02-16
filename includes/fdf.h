/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:58:01 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/16 14:56:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <math.h>
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

# define WHITE 0xffffff
# define RED 0xff0000
# define PI 3.142857

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_grid
{
	int		zoom;
	int		grid_height;
	int		grid_width;
	int		wire_len;
	int		x_angle;
	int		y_angle;
	int		grid_z_rotation;
	double	radian_x;
}	t_grid;

typedef struct s_line
{
	int	line_id;
	int	x_a;
	int	y_a;
	int	x_b;
	int	y_b;
	int	distance_x;
	int	distance_y;
}	t_line;

typedef struct s_point
{
	int				tab_x;
	int				tab_y;
	int				x;
	int				y;
	int				rotated_x;
	int				rotated_y;
	int				value;
	int				color;
	int				nb_line;
	int				elem_per_line;
	struct s_point	*left_point;
	struct s_point	*right_point;
	struct s_point	*above_point;
	struct s_point	*below_point;
}	t_point;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_point			***points;
	t_line			**lines;
	t_grid			grid;
	t_img			img;
	int				elem_per_line;
	int				nb_line;
	char			**line;
}	t_data;

/* fdf.c */
int				handle_no_event(void *data);
int				handle_input(int keysym, t_data *data);
void			img_pix_put(t_img *img, int x, int y, int color);
int				render(t_data *data);

/* point.c */
t_point			***parse_points(t_data data);
t_point			*init_initial_point(int x, int y, t_data data);
char			**get_data(int *nb_line, int *len, int fd);
int				get_nb_of_element_in_array(char **str);
void			get_rotated_point(t_data data, t_point *point, int *x, int *y);
t_point			 *init_right_point(t_data data, t_point *left_point, int x, int y);

/* connect.c */
void			connect_points(t_point ***points, t_data data);
void			add_right_point(t_point ***points, int i, int j, t_data data);
void			add_left_point(t_point ***points, int i, int j, t_data data);
void			add_above_point(t_point ***points, int i, int j);
void			add_below_point(t_point ***points, int i, int j, t_data data);

/* clear.c */
void			clear_split(char **str);
void			clear_point(t_data data);
void			clear_line(t_data data);

/* line.c */
t_line			**get_all_lines(t_data data);
t_line			*init_line(t_point *point_a, t_point *point_b, int line_id);
void			draw_line(t_data *data, t_line *line);

/* grid.c */
t_grid			init_grid(void);

#endif