/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-maga <vde-maga@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:17:43 by vde-maga          #+#    #+#             */
/*   Updated: 2025/05/12 16:27:39 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <fcntl.h> 
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>

static char	*ft_get_buffer(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(stash), free(buffer), NULL);
		buffer[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		if (temp)
			free(temp);
	}
	free(buffer);
	return (stash);
}

static char	*ft_get_line(char *stash)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!stash || stash[0] == '\0')
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	return (line);
}

static char	*ft_get_next(char *stash)
{
	char	*next;
	size_t	i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	next = ft_strdup(stash + i);
	if (!next)
		return (free(stash), NULL);
	free(stash);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_get_buffer(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	stash = ft_get_next(stash);
	return (line);
}
/*
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		printf("Uso: %s <nome_do_arquivo>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Erro ao abrir o arquivo");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
