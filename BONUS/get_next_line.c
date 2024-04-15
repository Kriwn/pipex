/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:00:39 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/15 19:45:38 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*clearline(char **file, size_t pos)
{
	char	*temp;
	char	*ans;

	ans = ft_substr(*file, 0, pos);
	if (!ans)
	{
		if (*file)
			free(*file);
		return (NULL);
	}
	temp = ft_substr(*file, pos, ft_strlen(*file));
	if (*file)
		free(*file);
	if (!temp)
		return (NULL);
	*file = temp;
	return (ans);
}

char	*ft_readline(char *file, char *buffer, int fd)
{
	ssize_t	len;

	len = 1;
	while (len > 0 && ft_strrchr(file, '\n') == NULL)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == -1)
		{
			if (file)
				free(file);
			free(buffer);
			return (NULL);
		}
		buffer[len] = '\0';
		file = ft_linejoin(file, buffer);
		if (!file)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (file);
}

char	*makebuff(char **file, int fd)
{
	char	*buffer;

	if (file[fd] == NULL)
	{
		file[fd] = ft_strdup("");
		if (!file[fd])
			return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		if (file[fd])
		{
			free(file[fd]);
			file[fd] = NULL;
		}
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*file[FD_MAX];
	char		*buffer;
	size_t		count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	count = 0;
	buffer = makebuff(file, fd);
	if (!buffer)
		return (NULL);
	file[fd] = ft_readline(file[fd], buffer, fd);
	if (!file[fd])
		return (NULL);
	if (!*file[fd])
	{
		if (file[fd])
			free(file[fd]);
		file[fd] = NULL;
		return (NULL);
	}
	while (file[fd][count] != '\0' && file[fd][count] != '\n')
		count++;
	count += (file[fd][count] == '\n');
	return (clearline(&file[fd], count));
}
