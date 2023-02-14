/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:58:01 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/14 21:30:48 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <X11/keysym.h>

# define WINDOW_WIDTH 720
# define WINDOW_HEIGHT 576

# define WHITE 0xffffff

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_line
{
	int	line_id;
	int	x_a;
	int	y_a;
	int	x_b;
	int	y_b;
	int	distance_x;
	int	distance_y;
	int	len;
	int	x_increment;
	int	y_increment;
}	t_line;

typedef struct s_point
{
	int				tab_x;
	int				tab_y;
	int				x;
	int				y;
	int				value;
	int				color;
	int				nb_line;
	int				elem_per_line;
	struct s_point	*left_point;
	struct s_point	*right_point;
	struct s_point	*above_point;
	struct s_point	*below_point;
}	t_point;

typedef struct s_parse_data
{
	int		elem_per_line;
	int		nb_line;
	char	**line;
}	t_parse_data;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_point			***points;
	t_line			**lines;
	t_parse_data	parsed_data;
	t_img			img;
}	t_data;


t_point	***parse_points(t_parse_data data);
t_point	*init_point(int x, int y, int value, t_parse_data data);
char	**get_parse_data(int *nb_line, int *len, int fd);
int		get_nb_of_element_in_array(char **str);

void	img_pix_put(t_img *img, int x, int y, int color);

void	connect_points(t_point ***points, t_parse_data data);
void	add_right_point(t_point ***points, int i, int j, t_parse_data data);
void	add_left_point(t_point ***points, int i, int j, t_parse_data data);
void	add_above_point(t_point ***points, int i, int j);
void	add_below_point(t_point ***points, int i, int j, t_parse_data data);

void	clear_split(char **str);
void	clear_point(t_point ***points, t_parse_data data);
void	clear_line(t_line **line, t_parse_data data);

t_line	**get_all_lines(t_point ***points, t_parse_data data);
t_line	*init_line(t_point *point_a, t_point *point_b, int line_id);
void	draw_line(t_data *data, t_line *line);

#endif