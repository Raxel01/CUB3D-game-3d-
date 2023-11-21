/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:32:10 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/20 11:54:02 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

char	*extract_line(char *buffer)
{
	int	i;

	i = 0;
	if (buffer)
	{
		while (buffer[i] && buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n')
			i++;
		return (ft_substr (buffer, 0, i));
	}
	return (NULL);
}

char	*to_stocked(char *rest)
{
	char	*stocked;
	int		i;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\0')
		return (NULL);
	stocked = ft_substr(rest, i + 1, (ft_strlen(rest) - (i + 1)));
	return (stocked);
}

char	*read_untilnl(char *joined, int fd)
{
	char		*buffer;
	ssize_t		data_readed;

	data_readed = 1;
	buffer = malloc((BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while (ft_strchr(joined) == 0 && data_readed != 0)
	{
		data_readed = read(fd, buffer, BUFFER_SIZE);
		if (data_readed == -1)
			return (free(buffer), NULL);
		if (data_readed == 0)
			return (free (buffer), joined);
		buffer[data_readed] = '\0';
		joined = ft_strjoin (joined, buffer);
	}
	free (buffer);
	return (joined);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stocked;
	char		*tmp;
	static int	flag;

	if (fd < 0 || BUFFER_SIZE <= 0 || flag == 1)
		return (NULL);
	stocked = read_untilnl(stocked, fd);
	if (stocked == NULL)
		return (NULL);
	if (stocked[0] == '\0')
	{
		flag = 1;
		return (free(stocked), NULL);
	}
	line = extract_line(stocked);
	tmp = stocked;
	stocked = to_stocked(tmp);
	free (tmp);
	return (line);
}
