/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:58:01 by llevasse          #+#    #+#             */
/*   Updated: 2023/02/12 00:51:16 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <X11/keysym.h>

# define WINDOW_WIDTH 1220
# define WINDOW_HEIGHT 1080

# define WHITE 0xffffff

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;

typedef struct s_point
{
	int				x;
	int				y;
	int				value;
	struct s_point	*left_point;
	struct s_point	*right_point;
	struct s_point	*above_point;
	struct s_point	*below_point;
}	t_point;

t_point	**parse_points(int fd);
t_point	*init_point(int x, int y);
char	**get_parse_data(int *nb_line, int *len, int fd);
int	get_nb_of_element_in_array(char **str);


#endif