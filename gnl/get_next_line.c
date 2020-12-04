/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:58:47 by jandre            #+#    #+#             */
/*   Updated: 2020/10/16 17:06:11 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*result;
	char	test;

	i = 0;
	test = (char)c;
	result = (char *)s;
	while (s[i])
	{
		if (s[i] == test)
			return (result + i);
		i++;
	}
	if (s[i] == c)
		return (result + i);
	return (NULL);
}

int		pos(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int		ft_initialize(int fd, char **line, char **rest)
{
	if (fd < 0 || fd > OPEN_MAX || !line)
		return (-1);
	if (rest[fd] == NULL)
	{
		if (!(rest[fd] = ft_strnew(0)))
			return (-1);
	}
	return (1);
}

int		ft_copy(char **rest, int fd)
{
	char	*ptr;

	if (ft_strchr(rest[fd], '\n'))
	{
		ft_strcpy(rest[fd], ft_strchr(rest[fd], '\n') + 1);
		return (1);
	}
	if (ft_strlen(rest[fd]) > 0)
	{
		ptr = rest[fd];
		rest[fd] = NULL;
		free(ptr);
		return (0);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*rest[OPEN_MAX];
	char		buffer[BUFFER_SIZE + 1];
	char		*ptr;
	int			ret;

	if (ft_initialize(fd, line, rest) < 0)
		return (-1);
	while (!(ft_strchr(rest[fd], '\n')) &&
			(ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		ptr = rest[fd];
		if (!(rest[fd] = ft_strjoin(rest[fd], buffer)))
		{
			free(rest[fd]);
			return (-1);
		}
		free(ptr);
	}
	if (ret < 0 || !(*line = ft_substr(rest[fd], 0, pos(rest[fd], '\n'))))
	{
		free(rest[fd]);
		return (-1);
	}
	free(*line);
	return (ft_copy(rest, fd));
}
