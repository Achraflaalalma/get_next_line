/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaalalm <alaalalm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:06:15 by alaalalm          #+#    #+#             */
/*   Updated: 2024/05/15 14:41:20 by alaalalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return ((char *)ft_calloc(1, sizeof(char)));
	s_len = ft_strlen(s);
	if (len > s_len - start)
		len = s_len - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*get_the_line(char *join)
{
	char	*get_line;

	get_line = ft_substr(join, 0, ft_strlen_n(join));
	if (!get_line)
		return (NULL);
	return (get_line);
}

char	*read_chars(int fd, char *join)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*temp_join;

	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(join, '\n'))
	{
		temp_join = join;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(join), NULL);
		else
		{
			buffer[bytes_read] = '\0';
			join = ft_strjoin(join, buffer);
			free(temp_join);
		}
	}
	return (free(buffer), join);
}

char	*polish(char *join)
{
	char			*updated_j;
	unsigned int	start;

	if (!join)
		return (NULL);
	start = ft_strlen_n(join);
	updated_j = ft_substr(join, start, ft_strlen(join) - start);
	if (!updated_j)
		return (free(join), NULL);
	free(join);
	return (updated_j);
}

char	*get_next_line(int fd)
{
	static char	*join;
	char		*get_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	if (!join)
		join = ft_calloc(1, sizeof(char));
	if (!join)
		return (NULL);
	join = read_chars(fd, join);
	if (!join)
		return (NULL);
	get_line = get_the_line(join);
	if (!get_line)
		return (free(join), NULL);
	join = polish(join);
	if (!join)
		return (NULL);
	if (ft_strlen(get_line) == 0)
	{
		free(join);
		join = NULL;
		return (free(get_line), NULL);
	}
	return (get_line);
}
