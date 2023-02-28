/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:58:01 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/28 11:02:35 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

/* 720p */
//# define WINDOW_WIDTH 1280
//# define WINDOW_HEIGHT 720

/* 1080p */
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define WHITE 0xffffff
# define HIGHEST_R 255
# define HIGHEST_G 0
# define HIGHEST_B 255
# define LOWEST_R 0
# define LOWEST_G 255
# define LOWEST_B 0
# define BEG_R 255
# define BEG_G 255
# define BEG_B 0
# define ZERO_R 255
# define ZERO_G 255
# define ZERO_B 255
# define RED 0xff0000
# define BG 0x000000
# define PI 3.142857

typedef struct s_img
{
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_grid
{
	double			zoom;
	int				grid_height;
	int				grid_width;
	int				wire_len;
	int				angle;
	int				grid_z_rotation;
	int    			x_decal;
	int    			y_decal;
	double			radian_x;
	double			iso_radian;
	int				iso_angle;
	int				z_amplifier;
}					t_grid;

typedef struct s_colour
{
	int				r;
	int				g;
	int				b;
	int				colour;
}					t_colour;

typedef struct s_point
{
	int				tab_x;
	int				tab_y;
	int				x;
	int				y;
	int				rotated_x;
	int				rotated_y;
	int				value;
	t_colour		color;
	int				nb_line;
	int				elem_per_line;
	struct s_point	*left_point;
	struct s_point	*right_point;
	struct s_point	*above_point;
	struct s_point	*below_point;
}					t_point;

typedef struct s_line
{
	int				line_id;
	int				x_a;
	int				x_b;
	int				distance_x;
	int				y_a;
	int				y_b;
	int				distance_y;
	int				len;
	int				altitude_a;
	int				altitude_b;
	int				z_ratio;
	t_colour		colour_a;
	t_colour		colour_b;
	t_point			*point_a;
	t_point			*point_b;
}					t_line;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_point			***points;
	t_line			**lines;
	t_grid			grid;
	t_img			img;
	t_colour		beg_colour;
	t_colour		zero_colour;
	int				elem_per_line;
	int				nb_line;
	char			**line;
	int				highest_altitude;
	int				lowest_altitude;
}					t_data;

typedef struct s_matrix
{
	int				**matrix;
	int				nb_rows;
	int				nb_column;
}					t_matrix;

/* fdf.c */
int					handle_no_event(void *data);
int					handle_input(int keysym, t_data *data);
void				img_pix_put(t_img *img, int x, int y, int color);
int					render(t_data *data);
void				print_grid_info(t_data *data);

/* parsing_data.c */
char				**get_data(int *nb_line, int *len, int fd);
int					get_nb_of_element_in_array(char **str);

/* point.c */
t_point				***parse_points(t_data data);
t_point				*init_point(t_data data, int x, int y, int z);
void				get_rotated_point(t_data data, int *x, int *y, int z);
void				set_colour(t_data *data);
t_colour			init_colour(int colour, int r, int g, int b);
t_colour			init_colour_from_str(const char *str);
double				get_iso_radian(int angle, int minus);
int					hex2int(char byte);

/* connect.c */
void				connect_points(t_point ***points, t_data data);
void				add_right_point(t_point ***points, int i, int j,
						t_data data);
void				add_left_point(t_point ***points, int i, int j,
						t_data data);
void				add_above_point(t_point ***points, int i, int j);
void				add_below_point(t_point ***points, int i, int j,
						t_data data);

/* clear.c */
void				clear_split(char **str);
void				clear_point(t_data data);
void				clear_line(t_data data);
void				reset_ptr_point(t_data data);
void				reset_ptr_lines(t_data data);

/* line.c */
t_line				**get_all_lines(t_data data);
t_line				*init_line(t_point *point_a, t_point *point_b, int line_id);
int					get_z_ratio(t_line *line);
void				draw_line(t_data *data, t_line *line);

/* grid.c */
t_grid				init_grid(void);
void				reset_grid(t_data *data);

/* colour.c */
int					get_highest_altitude(t_data data);
int					get_lowest_altitude(t_data data);
unsigned int		get_colour(t_line line, int i, t_data data);
int					get_dif(int a, int b);
int					get_len_with_high_altitude(t_line line, t_data data);
int					get_rgb(int r, int g, int b);

/* zoom.c */
void				zoom_in(t_data *data);
void				zoom_out(t_data *data);
void				reset_img(t_data *data);

/* rotate.c */
void				rotate_left(t_data *data, int value);
void				rotate_right(t_data *data, int value);
void				rotate_clockwise(t_data *data);
void				rotate_anticlockwise(t_data *data);
void				set_point(t_data *data);
void				set_point_follow_up(t_data data, t_point point, int *x, int *y);
void				set_lines(t_data *data);

/* move.c */
void				move_left(t_data *data, int value);
void				move_right(t_data *data, int value);
void				move_up(t_data *data, int value);
void				move_down(t_data *data, int value);

/* matrix.c */
void				free_matrix(t_matrix *matrix);
t_matrix			*init_matrix(int nb_rows, int nb_column);
t_matrix			*multiplie_matrix(t_matrix matrix_a, t_matrix matrix_b);

#endif