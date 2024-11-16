/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:44:05 by kevisout          #+#    #+#             */
/*   Updated: 2024/11/16 17:32:16 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cut_str(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	ret = malloc(ft_strlen(str) - i + 1);
	if (!ret)
		return (NULL);
	i++;
	while (str[i])
		ret[j++] = str[i++];
	ret[j] = '\0';
	free(str);
	return (ret);
}

int	check_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (-1);
}

char	*fill_line(char **stash, int ret)
{
	char	*line;

	if (ret < BUFFER_SIZE && check_nl(*stash) == -1)
	{
		line = ft_substr(*stash, 0, ft_strlen(*stash));
		return (free(*stash), *stash = NULL, line);
	}
	else if (check_nl(*stash) != -1)
	{
		line = ft_substr(*stash, 0, ft_strchr(*stash, '\n') - *stash + 1);
		return (*stash = cut_str(*stash), line);
	}
	return (NULL);
}

char	*init_stash(char *stash, int fd, char *buffer)
{
	int		ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret <= 0 && stash == NULL)
		return (free(buffer), NULL);
	buffer[ret] = '\0';
	if (!stash)
		stash = ft_substr(buffer, 0, ft_strlen(buffer));
	else
		stash = ft_strjoin(stash, buffer);
	free(buffer);
	if (stash[0] == '\0')
		return (free(stash), stash = NULL, NULL);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	int			ret;

	buffer = NULL;
	ret = 0;
	stash = init_stash(stash, fd, buffer);
	while (stash)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
			return (free(buffer), NULL);
		buffer[ret] = '\0';
		stash = ft_strjoin(stash, buffer);
		free(buffer);
		line = fill_line(&stash, ret);
		if (line)
			return (line);
	}
	return (NULL);
}
