/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 03:43:54 by achnouri          #+#    #+#             */
/*   Updated: 2024/12/29 09:31:30 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*join_strings(char *buff, char *buffer)
{
	char	*tmp;

	tmp = buff;
	buff = ft_strjoin(buff, buffer);
	return (free(tmp), tmp = NULL, buff);
}

static char	*read_file(int fd, char *buff)
{
	char	*buffer;
	ssize_t	readed;

	while (ft_strchr(buff, '\n') == NULL)
	{
		buffer = (char *)malloc(((size_t)(BUFFER_SIZE) + 1) * sizeof(char));
		if (!buffer)
			return (free(buff), buff = NULL, NULL);
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed <= 0)
		{
			free(buffer);
			buffer = NULL;
			if (readed == -1)
				return (free(buff), buff = NULL, NULL);
			break ;
		}
		buffer[readed] = '\0';
		buff = join_strings(buff, buffer);
		free(buffer);
		buffer = NULL;
		if (!buff)
			return (NULL);
	}
	return (buff);
}

static char	*extract_line(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	return (ft_substr(buff, 0, i));
}

static char	*remainder(char *buff)
{
	char	*new_buff;
	int		i;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i])
		i++;
	new_buff = ft_substr(buff, i, ft_strlen(buff) - i);
	return (free(buff), buff = NULL, new_buff);
}

char	*get_next_line(int fd)
{
	static char	*buff[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buff[fd] = read_file(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	line = extract_line(buff[fd]);
	if (!line)
		return (free(buff[fd]), buff[fd] = NULL, NULL);
	buff[fd] = remainder(buff[fd]);
	return (line);
}
