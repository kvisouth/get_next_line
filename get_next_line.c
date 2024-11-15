/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:44:05 by kevisout          #+#    #+#             */
/*   Updated: 2024/11/13 12:44:12 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* ft_strjoin from libft */
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	ret = malloc ((i + j + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	k = 0;
	i = 0;
	while (s1[i])
		ret[k++] = s1[i++];
	j = 0;
	while (s2[j])
		ret[k++] = s2[j++];
	ret[k] = '\0';
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	i = 0;
	while (s[i])
		i++;
	if (start >= i)
		return (ft_strdup(""));
	if (len > i - start)
		len = i - start;
	i = 0;
	while (i < len && s[i])
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start])
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str)
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*init_gnl(char *stash, int fd, char *buffer)
{
	char	*temp;
	int		ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = NULL;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	ret = read(fd, buff, BUFFER_SIZE);
	if (ret <= 0 && stash == NULL)
		return (free(buff), NULL);
	buff[ret] = '\0';
	temp = stash;
	stash = ft_strjoin(stash, buff);
	free(buff);
	free(temp);
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

	buff = NULL;
	ret = 0;
	stash = init_gnl(stash, fd, buff);

}
