/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tytang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:44:48 by tytang            #+#    #+#             */
/*   Updated: 2022/07/07 13:24:32 by tytang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*ft_read_and_save(int fd, char *save, char *buff)
{
	char	*backup;
	int		read_bytes;

	read_bytes = 1;
	while (read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		else if (read_bytes == 0)
			break ;
		if (!save)
			save = ft_strdup("");
		backup = save;
		buff[read_bytes] = '\0';
		save = ft_strjoin(backup, buff);
		free(backup);
		backup = NULL;
		if (ft_strchr(save, '\n'))
			break ;
	}
	return (save);
}

static char	*ft_save(char *line)
{
	size_t		i;
	char		*leftover;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	leftover = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*leftover == '\0')
	{
		free(leftover);
		leftover = NULL;
	}
	line[i + 1] = '\0';
	return (leftover);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buff;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc((BUFFER_SIZE + 1) * (sizeof (char)));
	if (!buff)
		return (NULL);
	line = ft_read_and_save(fd, save, buff);
	free(buff);
	buff = NULL;
	if (!line)
		return (line);
	save = ft_save(line);
	return (line);
}
