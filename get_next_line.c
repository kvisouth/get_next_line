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

/* Verifie si 'str' contient '\n' : 1 si oui, -1 si non. */
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

/* Retourne une ligne complete jusqu'a \n ou jusqu'a EOF depuis stash */
char	*fill_line(char **stash, int ret)
{
	char	*line;

	if (ret < BUFFER_SIZE && check_nl(*stash) == -1)
	{
		line = ft_substr(*stash, 0, ft_strlen(*stash));
		if (!line)
			return (NULL);
		return (free(*stash), *stash = NULL, line);
	}
	else if (check_nl(*stash) == 1)
	{
		line = ft_substr(*stash, 0, ft_strchr(*stash, '\n') - *stash + 1);
		if (!line)
			return (NULL);
		return (*stash = ft_cutstr(*stash), line);
	}
	return (NULL);
}

/* Initialise stash avec les premieres donnees lues depuis le fichier */
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

char	*read_buffer(int fd, char *stash, int *ret)
{
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	*ret = read(fd, buffer, BUFFER_SIZE);
	if (*ret == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[*ret] = '\0';
	stash = ft_strjoin(stash, buffer);
	free(buffer);
	return (stash);
}

/* Recupere la prochaine ligne d'un fichier (fd) */
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	int			ret;

	buffer = NULL;
	ret = 0;
	stash = init_stash(stash, fd, buffer);
	if (!stash)
		return (NULL);
	while (stash)
	{
		stash = read_buffer(fd, stash, &ret);
		if (!stash)
			return (NULL);
		line = fill_line(&stash, ret);
		if (line)
			return (line);
	}
	return (NULL);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main(int ac, char **av)
// {
// 	int i = 0;
// 	char *line;
// 	if (ac == 2)
// 	{
// 		int fd = open("test", O_RDONLY);
// 		while (i < atoi(av[1]))
// 		{
// 			line = get_next_line(fd);
// 			printf("%d: %s\n", i, line);
// 			free(line);
// 			i++;
// 		}
// 		while ((line = get_next_line(fd)) != NULL)
// 			free(line);
// 		close(fd);
// 	}
// 	return 0;
// }