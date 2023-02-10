/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:20:32 by llevasse          #+#    #+#             */
/*   Updated: 2023/01/23 11:12:59 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*stach = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buff, 0) != 0)
	{
		if (stach)
			return (free(stach), stach = NULL, NULL);
		return (NULL);
	}
	buff[0] = 0;
	stach = stach_empty(stach, fd, buff);
	if (!stach && buff[0] != 0)
		return (NULL);
	stach = check_stach_nl(stach, buff, fd);
	if (!stach)
		return (NULL);
	if (stach[0] == '\0')
		return (free(stach), stach = NULL, NULL);
	line = return_line(stach);
	if (!line)
		return (free(stach), stach = NULL, NULL);
	if (ft_strcmp(line, stach))
		return (get_left_over(line, stach), line);
	return (free(stach), stach = NULL, line);
}

char	*return_line(char *stach)
{
	char	*line;
	int		i;

	i = 0;
	while (stach[i] != '\n' && stach[i])
		i++;
	line = malloc((i + is_nl(stach) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	fill_char(line, stach, is_nl(stach));
	return (line);
}

char	*stach_empty(char *stach, int fd, char buff[BUFFER_SIZE])
{
	int	count;

	if (stach)
		return (stach);
	count = read(fd, buff, BUFFER_SIZE);
	buff[count] = '\0';
	if (count < 0)
		return (NULL);
	stach = malloc((count + 1) * sizeof(char));
	if (!stach)
		return (NULL);
	stach[count] = '\0';
	fill_char(stach, buff, 0);
	return (stach);
}

char	*check_stach_nl(char *stach, char buff[BUFFER_SIZE + 1], int fd)
{
	int	count;

	if (!stach)
		return (stach);
	if (!is_nl(stach))
	{
		count = read(fd, buff, BUFFER_SIZE);
		buff[count] = '\0';
		while (!is_nl(stach) && count > 0)
		{
			stach = ft_strjoin(stach, buff);
			if (!stach)
				return (NULL);
			if (!is_nl(stach))
				count = read(fd, buff, BUFFER_SIZE);
			buff[count] = '\0';
		}
		if (count <= 0)
			stach = ft_strjoin(stach, "\0");
		if (!stach)
			return (NULL);
	}
	return (stach);
}

void	get_left_over(char *line, char *stach)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i])
		stach[i++] = 0;
	if (!line[i])
		return (free(stach));
	i++;
	while (stach[i] != '\0')
		stach[j++] = stach[i++];
	stach[j] = 0;
}
