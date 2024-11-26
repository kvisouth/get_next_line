/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:12:45 by kevisout          #+#    #+#             */
/*   Updated: 2024/11/16 17:29:44 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Le meme ft_strlen que la libft */
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/* Le meme ft_strjoin que la libft a la difference qu'il free 's1' a la fin */
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	ret = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
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
	free((char *)s1);
	return (ret);
}

/* Le meme ft_strchr que la libft */
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

/* Le meme ft_substr que la libft */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	if (start >= ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
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

/* Coupe 'str' depuis '\n' et retourne ce qu'il y a apres. */
char	*ft_cutstr(char *str)
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
